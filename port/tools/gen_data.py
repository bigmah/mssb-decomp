#!/usr/bin/env python3
"""Generate C definitions for the data the PC build references but no game
source defines (the `lbl_*` objects of auto units, REL .rodata, ...).

    python3 port/tools/gen_data.py            # needs a built build/port (mssb_game)

1. Collect the undefined symbols of the game objects in build/port (nm),
   minus those the port or aurora provide (EXCLUDE).
2. Keep the ones that live in a data section of main.dol or a REL
   (config/GYQE01/**/symbols.txt).
3. For each, run tools/gendata.py on a source file that references it: the
   C type comes from that file's `extern` declaration, the initializer from
   orig/ (REL relocations become symbol references, so pointer fields are real
   pointers on PC). Symbols with no usable declaration become `u8[]` byte
   arrays marked TODO(port); those whose bytes look like pointers are listed
   in port/gen/REPORT.md.
4. Write port/gen/:
   - <module>_data.c: definitions of plain scalars/arrays (no headers needed;
     the PC prelude provides u8/f32/...).
   - <module>/<unit>.c: definitions that need the referencing file's types or
     refer to other symbols. The file starts with a declarations-only copy of
     the referencing source (function bodies and variable definitions
     removed), so the same types and prototypes are in scope.
   - sources.cmake: MSSB_GEN_SOURCES.

Rerun after decomp changes that add or retype data; the output is checked in.
"""
import collections, concurrent.futures as cf, json, os, re, struct, subprocess, sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
os.chdir(ROOT)
BUILD = os.environ.get('MSSB_PORT_BUILD', 'build/port')
OBJDIR = os.path.join(BUILD, 'CMakeFiles', 'mssb_game.dir')
GEN = 'port/gen'

# Defined outside the game sources on PC.
EXCLUDE = {
    '__float_nan', '__float_huge', '__double_huge',            # port/src/msl.c
    'GXNtsc480IntDf', 'GXNtsc480Int', 'GXMpal480IntDf',        # aurora
    'GXPal528IntDf', 'GXEurgb60Hz480IntDf',
}

MODULES = [('main', 'config/GYQE01/symbols.txt'), ('game', 'config/GYQE01/game/symbols.txt'),
           ('menus', 'config/GYQE01/menus/symbols.txt'), ('challenge', 'config/GYQE01/challenge/symbols.txt')]
DATA_SECTS = {'.data', '.sdata', '.sdata2', '.rodata', '.bss', '.sbss', '.sbss2'}


MOD_BY_NUM = {'1': 'challenge', '2': 'menus', '3': 'game'}


def name_encoded(sym, info):
    """(module, section, address, size) for decomp names like lbl_3_data_1D980
    that have no entry in symbols.txt (a part of a bigger object). The size runs
    to the next symbol."""
    m = re.match(r'lbl_([123])_(data|rodata|bss)_([0-9A-Fa-f]+)$', sym)
    if m:
        mod, sect, addr = MOD_BY_NUM[m.group(1)], '.' + m.group(2), int(m.group(3), 16)
    else:
        m = re.match(r'lbl_(8[0-9A-Fa-f]{7})$', sym)
        if not m:
            return None
        mod, addr = 'main', int(m.group(1), 16)
        sect = next((v[1] for v in info.values() if v[0] == 'main' and v[2] <= addr < v[2] + v[3]), None)
        if sect is None:
            return None
    nxt = min((v[2] for v in info.values() if v[0] == mod and v[1] == sect and v[2] > addr), default=addr + 4)
    return (mod, sect, addr, nxt - addr)


def nm_scan():
    defined, refs = set(), collections.defaultdict(list)
    for dp, _, fs in os.walk(OBJDIR):
        for f in sorted(fs):
            if not f.endswith('.o'):
                continue
            o = os.path.join(dp, f)
            src = o[len(OBJDIR):-2]
            if '/src/' not in src:
                continue  # generated objects (port/gen) don't count
            src = src[src.index('/src/') + 1:]
            for l in subprocess.run(['nm', '-g', o], capture_output=True, text=True).stdout.splitlines():
                p = l.split()
                if len(p) == 2 and p[0] == 'U':
                    refs[p[1][1:]].append(src)
                elif len(p) == 3:
                    defined.add(p[2][1:])
    return {s: sorted(set(v)) for s, v in refs.items() if s not in defined}, defined


def load_syms():
    info = {}
    for mod, path in MODULES:
        for l in open(path):
            m = re.match(r'(\S+) = (\.\w+):0x([0-9A-Fa-f]+);(.*)', l)
            if m and m.group(1) not in info:
                z = re.search(r'size:0x([0-9A-Fa-f]+)', m.group(4))
                info[m.group(1)] = (mod, m.group(2), int(m.group(3), 16), int(z.group(1), 16) if z else 0)
    return info


# ------------------------------------------------------------------ binaries
DOL = open('orig/GYQE01/sys/main.dol', 'rb').read()
_offs = struct.unpack('>18I', DOL[0:72]); _addrs = struct.unpack('>18I', DOL[72:144]); _sizes = struct.unpack('>18I', DOL[144:216])


def dol_read(a, n):
    for i in range(18):
        if _addrs[i] <= a and a + n <= _addrs[i] + _sizes[i]:
            return DOL[_offs[i] + a - _addrs[i]: _offs[i] + a - _addrs[i] + n]
    return None


_rel_cache = {}


def rel_info(mod):
    """(section data by name, set of relocated offsets per section name)"""
    if mod in _rel_cache:
        return _rel_cache[mod]
    rel = open('orig/GYQE01/files/%s.rel' % mod, 'rb').read()
    nsec, secoff = struct.unpack('>II', rel[0xC:0x14])
    rsec = [struct.unpack('>II', rel[secoff + 8 * i: secoff + 8 * i + 8]) for i in range(nsec)]
    names = re.findall(r'^\t(\.\w+)\s+type:', open('config/GYQE01/%s/splits.txt' % mod).read().split('\n\n')[0], re.M)
    byidx = {i + 1: n for i, n in enumerate(names)}
    impoff, impsize = struct.unpack('>II', rel[0x28:0x30])
    relocs = collections.defaultdict(set)
    for k in range(impsize // 8):
        _, roff = struct.unpack('>II', rel[impoff + 8 * k: impoff + 8 * k + 8])
        pos = roff; cur = 0; sec = 0
        while True:
            off, typ, tsec, add = struct.unpack('>HBBI', rel[pos:pos + 8]); pos += 8
            cur += off
            if typ == 203:
                break
            if typ == 202:
                sec = tsec; cur = 0; continue
            if typ == 1:
                relocs[byidx.get(sec)].add(cur)
    secs = {}
    for i, (so, ss) in enumerate(rsec):
        so &= ~1
        if i in byidx and so:
            secs[byidx[i]] = rel[so:so + ss]
    _rel_cache[mod] = (secs, relocs)
    return _rel_cache[mod]


def looks_like_pointers(mod, sect, addr, size):
    """Offsets inside the object that hold (probable) pointers."""
    if mod == 'main':
        raw = dol_read(addr, size)
        if raw is None:
            return []
        return [o for o in range(0, size - 3, 4)
                if 0x80003000 <= int.from_bytes(raw[o:o + 4], 'big') < 0x81800000]
    _, relocs = rel_info(mod)
    return sorted(o - addr for o in relocs.get(sect, ()) if addr <= o < addr + size)


def obj_bytes(mod, sect, addr, size):
    if mod == 'main':
        return dol_read(addr, size)
    secs, _ = rel_info(mod)
    s = secs.get(sect)
    return None if s is None else s[addr:addr + size]


# ------------------------------------------------------------------ gendata
ALIASES = set()   # symbols without a symbols.txt entry (see name_encoded)
REL_SECIDX = {}


def gendata_addr_args(sym, info):
    if sym not in ALIASES:
        return ()
    mod, sect, addr, size = info
    if mod != 'main':
        if mod not in REL_SECIDX:
            names = re.findall(r'^\t(\.\w+)\s+type:', open('config/GYQE01/%s/splits.txt' % mod).read().split('\n\n')[0], re.M)
            REL_SECIDX[mod] = {n: i + 1 for i, n in enumerate(names)}
        addr += REL_SECIDX[mod][sect] << 28
    return ('--addr', '%X' % addr, '--size', '%X' % size)


def run_gendata(src, sym, mod, extra=()):
    r = subprocess.run([sys.executable, 'tools/gendata.py', src, sym, '--module', mod, '--nonmatching', *extra],
                       capture_output=True, text=True)
    if r.returncode != 0 or not r.stdout.strip():
        return None, r.stderr
    return r.stdout, r.stderr


def multi_decl_type(src, sym):
    """`extern f32 a, b, c;` style declarations gendata can't parse."""
    txt = open(src).read()
    m = re.search(r'extern\s+((?:const\s+)?\w+)\s+[^;]*\b' + re.escape(sym) + r'\b[^;]*;', txt)
    return m.group(1) if m else None


def type_size(err):
    m = re.search(r'// SIZE 0x([0-9A-Fa-f]+)', err)
    return int(m.group(1), 16) if m else 0


def rename(defn, sym, mod, sect, addr, size, tsize):
    """Define the object under a private C name bound to the real symbol
    (GEN_SYM), so it can't clash with the referencing file's declaration of it
    (which may use a different or smaller type). Objects declared smaller than
    their symbol get the rest of the symbol's bytes appended (raw, big-endian:
    TODO(port) if used), .bss ones twice that for 64-bit layouts."""
    lines = defn.splitlines()
    k = next(i for i, l in enumerate(lines) if re.search(r'\b' + re.escape(sym) + r'\b', l) and not l.startswith('extern'))
    m = re.match(r'^(.*?)\b' + re.escape(sym) + r'\b((?:\[[^\]]*\])*)(\s*=.*|\s*;.*)$', lines[k])
    spec, dims, rest = m.group(1).strip(), m.group(2), m.group(3)
    rest_n = size - tsize if size and tsize and tsize < size else 0
    bss = sect in ('.bss', '.sbss', '.sbss2')
    if not rest_n:
        lines[k] = '%s __gen_%s%s GEN_SYM(%s)%s' % (spec, sym, dims, sym, rest)
        return '\n'.join(lines) + '\n'
    if bss:
        lines[k] = 'struct { %s head%s; u8 rest[0x%X]; } __gen_%s GEN_SYM(%s); // symbol is 0x%X bytes' % (
            spec, dims, rest_n * 2, sym, sym, size)
        return '\n'.join(lines) + '\n'
    raw = obj_bytes(mod, sect, addr + tsize, rest_n) or bytes(rest_n)
    init = '\n'.join(lines[k:]).split('=', 1)[1].rstrip().rstrip(';')
    rows = ',\n    '.join(', '.join('0x%02X' % b for b in raw[i:i + 16]) for i in range(0, len(raw), 16))
    tail = ('// TODO(port): the symbol is 0x%X bytes but declared as 0x%X; the rest is raw big-endian bytes\n'
            'struct { %s head%s; u8 rest[0x%X]; } __gen_%s GEN_SYM(%s) = {%s, {\n    %s,\n}};' % (
                size, tsize, spec, dims, rest_n, sym, sym, init, rows))
    return '\n'.join(lines[:k] + [tail]) + '\n'


def generate(sym, srcs, info):
    mod, sect, addr, size = info
    notes = []
    extra = gendata_addr_args(sym, info)
    for src in srcs:
        out, err = run_gendata(src, sym, mod, extra)
        if out:
            return src, out, [l for l in err.splitlines() if 'WARNING' in l or 'NOTE' in l], type_size(err)
    for src in srcs:
        t = multi_decl_type(src, sym)
        if t:
            out, err = run_gendata(src, sym, mod, ('--type', t) + extra)
            if out:
                return src, out, notes, type_size(err)
    # No declaration: a byte array of the symbol's size.
    raw = obj_bytes(mod, sect, addr, size) if sect not in ('.bss', '.sbss', '.sbss2') else None
    ptrs = looks_like_pointers(mod, sect, addr, size) if raw else []
    tag = '// TODO(port): no C type for this object' + (' (holds pointers at %s)' % ', '.join('0x%X' % p for p in ptrs) if ptrs else '')
    if raw is None:
        body = 'u8 %s[0x%X]; %s\n' % (sym, max(size, 1), tag)
    else:
        rows = [', '.join('0x%02X' % b for b in raw[i:i + 16]) for i in range(0, len(raw), 16)]
        body = '%s\nu8 %s[0x%X] = {\n    %s,\n};\n' % (tag, sym, size, ',\n    '.join(rows))
    return None, body, ['bytes' + (' POINTERS' if ptrs else '')], size


# ------------------------------------------------------------------ declarations-only copy of a source
def strip_source(text):
    """Keep preprocessor lines, typedefs, struct/union/enum definitions, extern
    declarations and prototypes; drop function bodies and variable definitions."""
    out = []; i = 0; n = len(text); stmt = []; depth = 0

    def flush_stmt(s):
        s = s.strip()
        if not s:
            return
        flat = re.sub(r'\s+', ' ', s)
        if flat.startswith('typedef') or re.match(r'(extern\s)', flat):
            out.append(s + ';\n'); return
        if re.match(r'(static\s+|const\s+|volatile\s+)*(struct|union|enum)\b[^{=]*\{', flat):
            # type definition, maybe with declarators after the closing brace
            j = s.rindex('}')
            head = s[:j + 1]
            if re.match(r'(static\s+|const\s+|volatile\s+)*(struct|union|enum)\s+\w+\s*\{', re.sub(r'\s+', ' ', head)) or flat.startswith('enum'):
                head = re.sub(r'^(\s*(static|const|volatile)\s+)+', '', head)
                out.append(head + ';\n')
            return
        bare = re.sub(r'\b(ATTRIBUTE_ALIGN|DECL_SECT|__declspec)\s*\([^()]*\)|__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)', '', flat)
        if '=' not in bare and re.search(r'\b\w+\s*\(', bare) and not re.match(r'^[^(]*\(\s*\*+\s*\w+\s*\)', bare):
            out.append(s + ';\n'); return
        # variable definition: dropped

    while i < n:
        c = text[i]
        if text.startswith('//', i):
            j = text.find('\n', i); j = n if j < 0 else j
            i = j; continue
        if text.startswith('/*', i):
            j = text.find('*/', i + 2); i = n if j < 0 else j + 2; continue
        if c == '#' and (not ''.join(stmt).strip() or ''.join(stmt).endswith('\n')) and depth == 0:
            # preprocessor line (with continuations)
            j = i
            while True:
                k = text.find('\n', j)
                if k < 0:
                    k = n; break
                if text[k - 1] == '\\':
                    j = k + 1; continue
                break
            line = text[i:k]
            if not re.match(r'#\s*pragma\b', line):
                out.append(''.join(stmt)); stmt = []
                out.append(line + '\n')
            i = k + 1; continue
        if c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            stmt.append(text[i:j + 1]); i = j + 1; continue
        if c == '{':
            cur = ''.join(stmt)
            if depth == 0 and re.search(r'\)\s*(__attribute__\s*\(\(.*\)\)\s*)?$', cur.strip()) and '=' not in cur:
                # function definition: keep the prototype
                d = 0; j = i
                while j < n:
                    if text.startswith('//', j):
                        j = text.find('\n', j); continue
                    if text.startswith('/*', j):
                        j = text.find('*/', j) + 2; continue
                    if text[j] in '"\'':
                        q = text[j]; j += 1
                        while text[j] != q:
                            j += 2 if text[j] == '\\' else 1
                        j += 1; continue
                    if text[j] == '{':
                        d += 1
                    elif text[j] == '}':
                        d -= 1
                        if d == 0:
                            break
                    j += 1
                proto = cur.strip()
                if not re.search(r'\basm\b', proto):
                    flush_stmt(proto)
                stmt = []; i = j + 1; continue
            depth += 1
        elif c == '}':
            depth -= 1
        elif c == ';' and depth == 0:
            flush_stmt(''.join(stmt)); stmt = []; i += 1; continue
        stmt.append(c); i += 1
    return ''.join(x if x.endswith('\n') else '' for x in out)


# ------------------------------------------------------------------ main
def main():
    und, defined = nm_scan()
    info = load_syms()
    for s_ in und:
        if s_ not in info and s_ not in EXCLUDE:
            enc = name_encoded(s_, info)
            if enc:
                info[s_] = enc
                ALIASES.add(s_)
    todo = {s: v for s, v in und.items() if s not in EXCLUDE and s in info and info[s][1] in DATA_SECTS}
    print('undefined: %d, data to generate: %d' % (len(und), len(todo)))
    results = {}
    while todo:
        with cf.ThreadPoolExecutor(os.cpu_count() or 8) as ex:
            futs = {ex.submit(generate, s, srcs, info[s]): s for s, srcs in todo.items()}
            for f in cf.as_completed(futs):
                results[futs[f]] = f.result()
        # Objects only the generated data points to.
        new = {}
        for s, (src, text, _, _) in results.items():
            for ident in set(re.findall(r'\b[A-Za-z_]\w*\b', text)):
                if ident in info and info[ident][1] in DATA_SECTS and ident not in defined \
                        and ident not in results and ident not in EXCLUDE:
                    new.setdefault(ident, [src] if src else [])
        if new:
            print('pointed-to objects: %d' % len(new))
        todo = new

    simple = collections.defaultdict(list)   # module -> [(addr, text)]
    typed = collections.defaultdict(list)    # src -> [(addr, text)]
    report = []
    for s, (src, text, notes, tsize) in sorted(results.items(), key=lambda kv: (info[kv[0]][0], info[kv[0]][2])):
        mod, sect, addr, size = info[s]
        lines = [l for l in text.splitlines() if l.strip()]
        defn = '\n'.join(lines) + '\n'
        defn = re.sub(r'\binff\b', 'INFINITY', re.sub(r'\binf\b', '((double)INFINITY)', defn))
        body = defn.split('=', 1)[1] if '=' in defn else ''
        ids = re.findall(r'[A-Za-z_]\w*', re.sub(r'\b0x[0-9A-Fa-f]+\b|\b\d+(\.\d*)?(e[-+]?\d+)?f?\b', '', body))
        refers = any(x not in ('NAN', 'NULL', 'INFINITY', 'double') for x in ids)
        first = lines[0] if lines else ''
        prim = re.match(r'(static\s+)?(const\s+)?(volatile\s+)?(u8|s8|u16|s16|u32|s32|u64|s64|f32|f64|char|int|float|double|BOOL)\s+\w+', first)
        if prim and re.search(r'\[[^\]]*[A-Za-z_]', first):
            prim = None  # dimension uses a macro from the source
        if '/* TODO' in defn:
            report.append('- `%s` (%s %s 0x%X): pointer field holds a non-address value (see `/* TODO */`)' % (s, mod, sect, addr))
        if src is not None:
            defn = rename(defn, s, mod, sect, addr, size, tsize)
        if src is None or (prim and not refers and len(lines) == sum(1 for l in lines if not l.startswith('extern'))):
            simple[mod].append((addr, '// %s %s 0x%X\n%s' % (mod, sect, addr, defn)))
        else:
            typed[src].append((addr, '// %s %s 0x%X\n%s' % (mod, sect, addr, defn)))
        if s in ALIASES:
            report.append('- `%s` (%s %s 0x%X): no symbols.txt entry (inside another object); defined as a separate copy' % (s, mod, sect, addr))
        for nt in notes:
            nt = nt.replace('// ', '')
            report.append('- `%s` (%s %s 0x%X): %s' % (s, mod, sect, addr, nt if len(nt) < 120 else nt[:117] + '...'))

    os.makedirs(GEN, exist_ok=True)
    for f in os.listdir(GEN):
        p = os.path.join(GEN, f)
        if f.endswith('.c'):
            os.remove(p)
        elif os.path.isdir(p):
            for g in os.listdir(p):
                os.remove(os.path.join(p, g))
            os.rmdir(p)
    files = []
    hdr = ('// Generated by port/tools/gen_data.py from orig/. Do not edit.\n'
           '#define GEN_STR_(x) #x\n#define GEN_STR(x) GEN_STR_(x)\n'
           '#define GEN_SYM(s) __asm__(GEN_STR(__USER_LABEL_PREFIX__) #s)\n')
    for mod, items in sorted(simple.items()):
        path = '%s/%s_data.c' % (GEN, mod)
        with open(path, 'w') as fp:
            fp.write(hdr + '\n')
            for _, t in sorted(items):
                fp.write(t + '\n')
        files.append(path)
    for src, items in sorted(typed.items()):
        mod = src.split('/')[1]
        unit = os.path.splitext(os.path.relpath(src, 'src'))[0].replace('/', '_')
        path = '%s/%s/%s.c' % (GEN, mod, unit)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, 'w') as fp:
            fp.write(hdr + '// Declarations from %s, then its missing data.\n\n' % src)
            fp.write(strip_source(open(src).read()))
            fp.write('\n// ---- generated data ----\n\n')
            for _, t in sorted(items):
                fp.write(t + '\n')
        files.append(path)
    with open(GEN + '/sources.cmake', 'w') as fp:
        fp.write('# Generated by port/tools/gen_data.py\nset(MSSB_GEN_SOURCES\n')
        for p in sorted(files):
            fp.write('    ${CMAKE_SOURCE_DIR}/%s\n' % os.path.relpath(p, 'port'))
        fp.write(')\n')
    with open(GEN + '/REPORT.md', 'w') as fp:
        fp.write('# Generated data: objects to review\n\nByte arrays (no C type found) are `TODO(port)`; '
                 '`POINTERS` ones hold addresses and must get a real type before they are used.\n\n')
        fp.write('\n'.join(sorted(report)) + '\n')
    print('simple: %d, typed: %d (in %d files)' % (sum(len(v) for v in simple.values()),
                                                     sum(len(v) for v in typed.values()), len(typed)))


if __name__ == '__main__':
    main()
