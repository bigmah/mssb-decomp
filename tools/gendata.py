#!/usr/bin/env python3
"""Generate C definitions (with initialisers) for data objects of the original binaries.

One object:   tools/gendata.py src/main/file_80037054.c lbl_800F79B8
              tools/gendata.py src/game/rep_0610.c lbl_3_data_1234 --module game
A whole unit: tools/gendata.py --unit main/file_80037054.c        (all objects in its splits.txt
              ranges for .data/.sdata/.bss/.sbss, in address order; uninitialised ones bare)
              tools/gendata.py --unit game/rep_0610.c --module game

The C type comes from the unit's `extern T sym[...];` declaration (the unit is preprocessed with
clang -E and its struct layouts are parsed, bitfields included), or --type/--dims. Floats print in
shortest round-trip form; pointers become `&sym`, `sym`, a function name, a string literal (symbols
with data:string), or `(u8*)&container + off`; REL pointers are resolved through the REL's
relocations. Missing declarations for pointed-to objects/functions are printed as externs first.
Stderr notes: size mismatches against symbols.txt, non-zero bytes past the type, `// SIZE 0x..`.
Review the output: objects with no declaration get `u8[]` + `// TODO type`.
"""
import argparse, os, re, struct, subprocess, sys

ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
ap.add_argument('src', nargs='?'); ap.add_argument('sym', nargs='?')
ap.add_argument('--unit', help='unit path as in splits.txt (e.g. main/file_80037054.c): emit all its data')
ap.add_argument('--sects', default='.data,.sdata,.bss,.sbss', help='sections for --unit')
ap.add_argument('--module', default='main', help='main (DOL) or a REL module: game, menus, challenge')
ap.add_argument('--type'); ap.add_argument('--dims', default=None)
ap.add_argument('--name'); ap.add_argument('--static', action='store_true')
ap.add_argument('--addr'); ap.add_argument('--size')
ap.add_argument('--per', type=int, default=0)
ap.add_argument('--noauto', action='store_true', help='do not turn a struct declared once into an array')
ap.add_argument('--nonmatching', action='store_true', help='preprocess with NONMATCHING=1 (the PC build\'s view)')
args = ap.parse_args()
if args.unit:
    here = os.path.dirname(os.path.abspath(__file__))
    os.execv(sys.executable, [sys.executable, os.path.join(here, 'gendata_unit.py'), args.unit, '--module', args.module, '--sects', args.sects])
if not args.src or not args.sym:
    ap.error('need <src> <symbol> or --unit')

# ---------------------------------------------------------------- binary
# DOL objects use their real addresses. REL objects get virtual addresses (section index << 28) + offset.
REL = args.module != 'main'
d = open('orig/GYQE01/sys/main.dol', 'rb').read()
offs = struct.unpack('>18I', d[0:72]); addrs = struct.unpack('>18I', d[72:144]); sizes = struct.unpack('>18I', d[144:216])
relocs = {}
if REL:
    rel = open('orig/GYQE01/files/%s.rel' % args.module, 'rb').read()
    rel_id, = struct.unpack('>I', rel[0:4])
    nsec, secoff = struct.unpack('>II', rel[0xC:0x14])
    rsec = [struct.unpack('>II', rel[secoff + 8 * i: secoff + 8 * i + 8]) for i in range(nsec)]
    secnames = re.findall(r'^\t(\.\w+)\s+type:', open('config/GYQE01/%s/splits.txt' % args.module).read().split('\n\n')[0], re.M)
    secidx = {n: i + 1 for i, n in enumerate(secnames)}
    impoff, impsize = struct.unpack('>II', rel[0x28:0x30])
    for k in range(impsize // 8):
        mod, roff = struct.unpack('>II', rel[impoff + 8 * k: impoff + 8 * k + 8])
        pos = roff; cur = 0; sec = 0
        while True:
            off, typ, tsec, add = struct.unpack('>HBBI', rel[pos:pos + 8]); pos += 8
            cur += off
            if typ == 203: break
            if typ == 202: sec = tsec; cur = 0; continue
            if typ == 201: continue
            if typ == 1:  # R_PPC_ADDR32
                tgt = add if mod == 0 else (tsec << 28) + add
                relocs[(sec << 28) + cur] = tgt
def read(a, n):
    if REL and a < 0x80000000:
        i = a >> 28; o = a & 0x0FFFFFFF
        so, ss = rsec[i]; so &= ~1
        if so == 0 or o + n > ss: return None
        return rel[so + o: so + o + n]
    for i in range(18):
        if addrs[i] <= a and a + n <= addrs[i] + sizes[i]:
            return d[offs[i] + a - addrs[i]: offs[i] + a - addrs[i] + n]
    return None  # bss
symaddr = {}; symsize = {}; addr2sym = {}; symtype = {}
def load_syms(path, rel_mod):
    for l in open(path):
        m = re.match(r'(\S+) = (\.\w+):0x([0-9A-Fa-f]+);(.*)', l)
        if not m: continue
        a = int(m.group(3), 16)
        if rel_mod:
            if m.group(2) not in secidx: continue
            a += secidx[m.group(2)] << 28
        symaddr[m.group(1)] = a
        z = re.search(r'size:0x([0-9A-Fa-f]+)', m.group(4)); symsize[m.group(1)] = int(z.group(1), 16) if z else 0
        symtype[m.group(1)] = 'function' if 'type:function' in m.group(4) else ('string' if 'data:string' in m.group(4) else 'object')
        if not m.group(1).startswith(('jumptable_', '@', 'gap_', 'pad_')):
            addr2sym.setdefault(a, m.group(1))
load_syms('config/GYQE01/symbols.txt', False)
if REL: load_syms('config/GYQE01/%s/symbols.txt' % args.module, True)
sorted_syms = sorted((a, n) for n, a in symaddr.items() if not n.startswith(('jumptable_', '@', 'gap_', 'pad_')))

# ---------------------------------------------------------------- C types
pp = subprocess.run(['/usr/bin/clang', '-E', '-P', '-Iinclude', '-Iinclude/stl', '-DNONMATCHING=%d' % args.nonmatching, '-w', args.src],
                    capture_output=True, text=True).stdout
pp = re.sub(r'__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)', '', pp)
pp = re.sub(r'__declspec\s*\([^)]*\)', '', pp)
pp = re.sub(r'(?m)^\s*#.*$', '', pp)
PRIM = {'char': (1, 's'), 'signed char': (1, 's'), 'unsigned char': (1, 'u'), 'short': (2, 's'), 'short int': (2, 's'),
        'signed short': (2, 's'), 'unsigned short': (2, 'u'), 'unsigned short int': (2, 'u'), 'int': (4, 's'),
        'signed int': (4, 's'), 'signed': (4, 's'), 'unsigned int': (4, 'u'), 'unsigned': (4, 'u'), 'long': (4, 's'),
        'signed long': (4, 's'), 'unsigned long': (4, 'u'), 'long int': (4, 's'), 'unsigned long int': (4, 'u'),
        'long long': (8, 's'), 'unsigned long long': (8, 'u'), 'signed long long': (8, 's'), 'float': (4, 'f'),
        'double': (8, 'f'), 'long double': (8, 'f'), '_Bool': (1, 'u'), 'void': (0, 'v')}
typedefs = {}   # name -> type
lazy = {}       # typedef name -> 'struct X' defined later
structs = {}    # 'struct X' -> type
class T:
    def __init__(s, kind, size=0, align=1, **kw):
        s.kind = kind; s.size = size; s.align = align; s.__dict__.update(kw)
def prim(name):
    sz, sg = PRIM[name]; return T('prim', sz, max(sz, 1), sign=sg, name=name)
PTR = T('ptr', 4, 4)

def split_top(s, sep):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '({[': depth += 1
        elif ch in ')}]': depth -= 1
        if ch == sep and depth == 0: out.append(cur); cur = ''
        else: cur += ch
    if cur.strip(): out.append(cur)
    return out

def evalc(e):
    e = re.sub(r'(\d+)[uUlL]+\b', r'\1', e.strip())
    e = re.sub(r'\b([A-Za-z_]\w*)\b', lambda m: str(consts[m.group(1)]) if m.group(1) in consts else m.group(1), e)
    e = re.sub(r'sizeof\s*\(\s*([^()]+)\s*\)', lambda m: str(base_type(m.group(1)).size), e)
    return int(eval(e.replace('/', '//')))

def base_type(spec):
    spec = re.sub(r'\b(const|volatile|static|extern|register|inline)\b', '', spec).strip()
    spec = re.sub(r'\s+', ' ', spec)
    if spec in PRIM: return prim(spec)
    m = re.match(r'(struct|union) (\w+)$', spec)
    if m:
        k = m.group(1) + ' ' + m.group(2)
        if k not in structs: raise KeyError('incomplete ' + k)
        return structs[k]
    if spec.startswith('enum'): return T('prim', 4, 4, sign='s', name='int')
    if spec in typedefs: return typedefs[spec]
    if spec in lazy: return base_type(lazy[spec])
    raise KeyError('unknown type ' + repr(spec))

def apply_declarator(bt, decl, spec=None):
    """returns (name, type) for declarator text like '*name[3][4]' or '(*fn)(int)'"""
    decl = decl.strip().lstrip('*').strip() if re.match(r'^\*+\s*\(', decl.strip()) else decl.strip()
    m = re.match(r'\(\s*\*\s*(\w+)\s*\)\s*\(.*\)$', decl, re.S)
    if m: return m.group(1), PTR
    m = re.match(r'\(\s*\*\s*(\w+)\s*\)((?:\s*\[[^\]]*\])+)$', decl)
    if m: return m.group(1), PTR
    stars = len(decl) - len(decl.lstrip('*'))
    decl = decl.lstrip('*').strip()
    decl = re.sub(r'\b(const|volatile)\b', '', decl).strip()
    m = re.match(r'(\w+)\s*((?:\[[^\]]*\]\s*)*)(?::\s*(\d+))?$', decl)
    if not m: raise ValueError('declarator ' + decl)
    if not stars and bt is None: raise KeyError('incomplete type for ' + decl)
    t = T('ptr', 4, 4, pointee=(re.sub(r'\b(const|volatile)\b', '', spec).strip() if spec and stars == 1 else None)) if stars else bt
    if m.group(3):
        return m.group(1), T('bits', t.size, t.align, width=int(m.group(3)), sign=t.sign)
    dims = re.findall(r'\[([^\]]*)\]', m.group(2))
    for dim in reversed(dims):
        n = evalc(dim) if dim.strip() else 0
        t = T('array', t.size * n, t.align, elem=t, n=n)
    return m.group(1), t

def layout(kind, body):
    fields = []; off = 0; align = 1; size = 0; bit = None
    for decl in split_top(body, ';'):
        decl = decl.strip()
        if not decl: continue
        m = re.match(r'(struct|union)\s*(\w*)\s*\{(.*)\}\s*(.*)$', decl, re.S)
        if m:
            sub = layout(m.group(1), m.group(3))
            if m.group(2): structs[m.group(1) + ' ' + m.group(2)] = sub
            items = [(m.group(4), sub)] if m.group(4).strip() else [('', sub)]
            resolved = [apply_declarator(sub, x) if x.strip() else ('', sub) for x, _ in items]
        else:
            # split base type and declarators
            mm = re.match(r'((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*[\w]+(?:\s+(?:int|long|short|char|double)\b)*)\s*(.*)$', decl, re.S)
            try: bt = base_type(mm.group(1))
            except KeyError: bt = None
            resolved = [apply_declarator(bt, x, mm.group(1)) for x in split_top(mm.group(2), ',')]
        for name, t in resolved:
            if kind == 'union':
                fields.append((name, 0, t)); size = max(size, t.size)
            elif t.kind == 'bits':
                if bit is None: bit = off * 8
                fields.append((name, bit, t)); bit += t.width
                off = (bit + 7) // 8
            else:
                if bit is not None:
                    off = (bit + 7) // 8; bit = None
                off = (off + t.align - 1) & ~(t.align - 1)
                fields.append((name, off, t)); off += t.size
            align = max(align, t.align)
    if kind == 'struct': size = off
    size = (size + align - 1) & ~(align - 1)
    return T(kind, size, align, fields=fields)

# walk top-level statements in source order
consts = {}
def statements(text):
    out = []; depth = 0; cur = []; i = 0; n = len(text)
    while i < n:
        ch = text[i]
        if ch == '{':
            if depth == 0 and re.search(r'\)\s*$', ''.join(cur)):   # function body: skip
                k = i; dd = 0
                while True:
                    if text[k] == '{': dd += 1
                    elif text[k] == '}':
                        dd -= 1
                        if dd == 0: break
                    k += 1
                cur = []; i = k + 1; continue
            depth += 1
        elif ch == '}': depth -= 1
        elif ch == ';' and depth == 0:
            out.append(''.join(cur).strip()); cur = []; i += 1; continue
        cur.append(ch); i += 1
    return out
def do_enum(body):
    v = -1
    for item in split_top(body, ','):
        item = item.strip()
        if not item: continue
        if '=' in item:
            nm, ex = item.split('=', 1)
            try: v = evalc(ex)
            except Exception: v = v + 1
        else:
            nm = item; v = v + 1
        consts[nm.strip()] = v
for st in statements(pp):
    try:
        td = st.startswith('typedef')
        body_st = st[7:].strip() if td else st
        m = re.match(r'(?:(?:const|volatile|static|extern)\s+)*(struct|union|enum)\s*(\w*)\s*\{', body_st)
        if m:
            depth = 0; j = m.end() - 1
            while True:
                if body_st[j] == '{': depth += 1
                elif body_st[j] == '}':
                    depth -= 1
                    if depth == 0: break
                j += 1
            body = body_st[m.end():j]; tail = body_st[j + 1:]
            if m.group(1) == 'enum':
                do_enum(body); t = T('prim', 4, 4, sign='s', name='int')
                if m.group(2): structs['enum ' + m.group(2)] = t
            else:
                t = layout(m.group(1), body)
                if m.group(2): structs[m.group(1) + ' ' + m.group(2)] = t
            if td:
                for x in split_top(tail, ','):
                    nm, tt = apply_declarator(t, x); typedefs[nm] = tt
            continue
        if td:
            fm = re.match(r'[^()]*\(\s*\*\s*(\w+)\s*\)\s*\(', body_st, re.S)
            if fm: typedefs[fm.group(1)] = PTR; continue
            fm = re.match(r'[^()]*?\b(\w+)\s*\(', body_st, re.S)   # function type typedef
            mm = re.match(r'((?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*[\w]+(?:\s+(?:int|long|short|char|double)\b)*)\s*(.*)$', body_st, re.S)
            if mm:
                if mm.group(1).startswith(('struct', 'union')) and mm.group(1).split()[-1] and (mm.group(1) not in structs):
                    # forward-declared tag: resolve lazily
                    pass
                bt0 = None
                try: bt0 = base_type(mm.group(1))
                except KeyError: bt0 = None
                for x in split_top(mm.group(2), ','):
                    if bt0 is None:
                        if x.strip().startswith('*'): typedefs[x.strip().lstrip('*').strip()] = PTR
                        else: lazy[x.strip()] = mm.group(1)
                        continue
                    nm, tt = apply_declarator(bt0, x, mm.group(1)); typedefs[nm] = tt
    except Exception as e:
        if os.environ.get('GD_DEBUG'): print('skip', st[:60].replace('\n', ' '), repr(e), file=sys.stderr)

# ---------------------------------------------------------------- the object's type
sym = args.sym
if args.type:
    tspec, dims = args.type, args.dims or ''
else:
    m = re.search(r'extern\s+([^;]*?)\b' + re.escape(sym) + r'\b\s*((?:\[[^\]]*\])*)\s*;', pp)
    if not m: sys.exit('no extern declaration of %s; pass --type' % sym)
    tspec, dims = m.group(1).strip(), args.dims if args.dims is not None else m.group(2)
stars = tspec.count('*'); tspec = tspec.replace('*', '').strip()
bt = T('ptr', 4, 4, pointee=re.sub(r'\b(const|volatile)\b', '', tspec).strip() if stars == 1 else None) if stars else base_type(tspec)
addr = int(args.addr, 16) if args.addr else symaddr[sym]
size = int(args.size, 16) if args.size else symsize.get(sym, 0)
dl = re.findall(r'\[([^\]]*)\]', dims)
if dl and not dl[0].strip():
    inner = bt
    for dd in reversed(dl[1:]): inner = T('array', inner.size * evalc(dd), inner.align, elem=inner, n=evalc(dd))
    n0 = size // inner.size
    dl[0] = str(n0)
t = bt
for dd in reversed(dl):
    n = evalc(dd); t = T('array', t.size * n, t.align, elem=t, n=n)

if not dl and size and t.size and size % t.size == 0 and size // t.size > 1 and t.kind == 'struct' and '--noauto' not in sys.argv:
    tail_ = read(addr + t.size, size - t.size)
    if tail_ is None or any(tail_):
        n_ = size // t.size
        dl = [str(n_)]
        t = T('array', t.size * n_, t.align, elem=t, n=n_)
        print('// NOTE: declared as one %s, symbol holds %d' % (tspec, n_), file=sys.stderr)
data = read(addr, t.size)
if size > t.size:
    extra_ = read(addr + t.size, size - t.size)
    if extra_ is not None and any(extra_):
        print('// WARNING: 0x%X bytes past the type are not zero: %s' % (size - t.size, extra_.hex()), file=sys.stderr)
def fmt_f(v, dbl):
    if v != v: return 'NAN'
    for p in range(6, 18):
        s = '%.*g' % (p, v)
        if (float(s) == v) if dbl else (struct.unpack('>f', struct.pack('>f', float(s)))[0] == v): break
    if 'e' not in s and '.' not in s and 'inf' not in s: s += '.0'
    return s + ('' if dbl else 'f')
_covered = None
needed = {}
def covered():
    global _covered
    if _covered is None:
        _covered = []
        for dm in re.finditer(r'extern\s+([^;()]*?)\s*\b(lbl_\w+)\b\s*((?:\[[^\]]*\])*)\s*;', pp):
            n = dm.group(2)
            if n not in symaddr: continue
            try:
                spec = dm.group(1).strip(); st = spec.count('*'); spec = spec.replace('*', '').strip()
                tt = PTR if st else base_type(spec)
                for dd in reversed(re.findall(r'\[([^\]]*)\]', dm.group(3))):
                    if not dd.strip(): tt = None; break
                    k = evalc(dd); tt = T('array', tt.size * k, tt.align, elem=tt, n=k)
                if tt is not None and tt.size > symsize.get(n, 0):
                    _covered.append((symaddr[n], symaddr[n] + tt.size, n))
            except Exception:
                pass
    return _covered
def cstr(b):
    out = '"'; prev_esc = False
    for ch in b:
        c = chr(ch)
        if ch == 0x0A: t = '\\n'; esc = False
        elif ch == 0x22: t = '\\"'; esc = False
        elif ch == 0x5C: t = '\\\\'; esc = False
        elif 0x20 <= ch < 0x7F:
            t = c; esc = False
            if prev_esc and c in '0123456789abcdefABCDEF': t = '" "' + c
        else: t = '\\x%02X' % ch; esc = True
        out += t; prev_esc = esc
    return out + '"'
def ptrval(v, pointee=None):
    if v == 0: return 'NULL'
    if v in addr2sym and symtype.get(addr2sym[v]) == 'string':
        raw = read(v, symsize[addr2sym[v]]) or b''
        if b'\0' in raw: return cstr(raw[:raw.index(b'\0')])
    for (ca, cb, cn) in covered():
        if ca < v < cb:
            return '(void*)((u8*)&%s + 0x%X)' % (cn, v - ca)
    if v in addr2sym:
        n = addr2sym[v]
        if symtype.get(n) == 'function':
            if not re.search(r'\b' + re.escape(n) + r'\s*\(', pp) and n not in needed:
                g = subprocess.run(['grep', '-rhE', r'^[A-Za-z][^;={}]*\b' + n + r'\s*\([^;{]*\)\s*;', 'include', 'src'],
                                   capture_output=True, text=True).stdout.strip().splitlines()
                needed[n] = (re.sub(r'^\s*extern\s+', '', g[0]).split(';')[0] + ';') if g else 'void %s(); // TODO prototype' % n
            return n
        dm = re.search(r'extern\s+([^;()]*?)\s*\b' + re.escape(n) + r'\b\s*((?:\[[^\]]*\])*)\s*;', pp)
        if not dm and not re.search(r'\b' + re.escape(n) + r'\b', pp):
            pt = pointee if pointee and pointee != 'void' else 'u8'
            needed[n] = 'extern %s %s[];%s' % (pt, n, '' if pointee and pointee != 'void' else ' // TODO type')
            return n if pt != 'u8' or pointee in ('u8', 'unsigned char') else '(void*)' + n
        if dm and pointee:
            tspec_ = re.sub(r'\b(const|volatile)\b', '', dm.group(1)).strip()
            if tspec_ == pointee: return n if dm.group(2) else '&' + n
            if pointee == 'void': return n if dm.group(2) else '&' + n
        return '(void*)&' + n
    # inside an object
    import bisect
    k = bisect.bisect_right(sorted_syms, (v, '\xff')) - 1
    if k >= 0:
        a, n = sorted_syms[k]
        if v < a + max(symsize.get(n, 0), 1):
            return '(void*)((u8*)&%s + 0x%X) /* TODO type */' % (n, v - a)
    return '(void*)0x%08X /* TODO */' % v
def emit(t, off, indent):
    if t.kind == 'prim':
        raw = data[off:off + t.size]
        if t.sign == 'f': return fmt_f(struct.unpack('>f' if t.size == 4 else '>d', raw)[0], t.size == 8)
        v = int.from_bytes(raw, 'big', signed=(t.sign == 's'))
        if t.sign == 'u' and t.size >= 4 and v > 0xFFFF: return '0x%X' % v
        return str(v)
    if t.kind == 'bits':
        whole = int.from_bytes(data, 'big'); total = len(data) * 8
        v = (whole >> (total - off - t.width)) & ((1 << t.width) - 1)
        return str(v)
    if t.kind == 'ptr':
        v = int.from_bytes(data[off:off + 4], 'big')
        if REL: v = relocs.get(addr + off, v)
        return ptrval(v, getattr(t, 'pointee', None))
    if t.kind == 'array':
        items = [emit(t.elem, off + i * t.elem.size, indent + 1) for i in range(t.n)]
        flat = all('\n' not in x for x in items) and sum(len(x) + 2 for x in items) < 100
        if flat: return '{' + ', '.join(items) + '}'
        per = args.per or (16 if t.elem.kind == 'prim' and t.elem.size == 1 else 8 if t.elem.kind == 'prim' else 1)
        rows = [', '.join(items[i:i + per]) for i in range(0, len(items), per)]
        pad = '    ' * (indent + 1)
        return '{\n' + ',\n'.join(pad + r for r in rows) + ',\n' + '    ' * indent + '}'
    if t.kind == 'union':
        name, o, ft = t.fields[0]
        return '{' + emit(ft, off + o, indent) + '}'
    items = [emit(ft, (off * 8 + o) if ft.kind == 'bits' else off + o, indent + 1) for (name, o, ft) in t.fields]
    if all('\n' not in x for x in items) and sum(len(x) + 2 for x in items) < 110:
        return '{' + ', '.join(items) + '}'
    pad = '    ' * (indent + 1)
    return '{\n' + ',\n'.join(pad + x for x in items) + ',\n' + '    ' * indent + '}'
body_ = emit(t, 0, 0) if data is not None else None
for k_, v_ in needed.items(): print(v_)
if data is None:
    print('%s%s %s%s;' % ('static ' if args.static else '', tspec + ' ' + '*' * stars, args.name or sym, ''.join('[%s]' % x for x in dl)))
else:
    print('%s%s %s%s%s = %s;' % ('static ' if args.static else '', tspec, '*' * stars, args.name or sym,
                                 ''.join('[%s]' % x for x in dl), body_))
print('// SIZE 0x%X' % t.size, file=sys.stderr)
if size and t.size != size:
    print('// NOTE: type size 0x%X != symbol size 0x%X' % (t.size, size), file=sys.stderr)
