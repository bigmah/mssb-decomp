#!/usr/bin/env python3
"""Rewrite the views of a global so their fields land where the canonical view
has them on PC (see port/tools/viewcheck.py).

    python3 port/tools/pcview.py <global> [--canon Type] [--dry-run]

For each view of <global> that viewcheck flags, the typedef gets a TARGET_PC
branch: a union of one-field structs, each field preceded by padding up to
its PC offset (the canonical view's PC offset of the field that covers the
same GameCube offset, plus the distance into it). The GameCube branch keeps
the original typedef. Offsets are numbers: rerun after the canonical struct
changes (viewcheck reports it).
"""
import os, re, subprocess, sys, functools

R = os.getcwd()
PC = ['/usr/bin/clang', '-fsyntax-only', '-ferror-limit=0', '-Wno-everything', '-DNDEBUG=1', '-DNONMATCHING=1', '-DTARGET_PC',
      '-DVERNUM=0', '-DVERSION=0', '-Iport/include_game', '-Iport/include', '-Iport/extern/aurora/include', '-Iinclude', '-std=gnu11',
      '-arch', 'arm64', '-fsigned-char', '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=0', '-include', 'port/include/port/prelude.h',
      '-Xclang', '-fdump-record-layouts']
GC = ['/usr/bin/clang', '-target', 'powerpc-unknown-eabi', '-fsyntax-only', '-ferror-limit=0', '-nostdinc', '-Iinclude',
      '-Iinclude/stl', '-DNONMATCHING=1', '-fsigned-char', '-Wno-everything', '-Xclang', '-fdump-record-layouts']
if not os.path.isdir('port/include_game'):
    PC.remove('-Iport/include_game')


@functools.lru_cache(None)
def dump(f, plat):
    r = subprocess.run((PC if plat == 'pc' else GC) + [f], capture_output=True, text=True, cwd=R)
    recs, sizes, cur = {}, {}, None
    for l in r.stdout.split('\n'):
        if l.startswith('*** Dumping AST Record Layout'):
            cur = None
            continue
        m = re.match(r'\s*\| \[sizeof=(\d+)', l)
        if m and cur and cur not in sizes:
            sizes[cur] = int(m.group(1))
        m = re.match(r'\s*(\d+) \|( *)(.*)$', l)
        if not m:
            continue
        off, ind, rest = int(m.group(1)), len(m.group(2)), m.group(3)
        if ind == 1:
            mm = re.match(r'(?:struct|union) (\w+)', rest)
            cur = None
            if mm and mm.group(1) not in recs:
                cur = mm.group(1)
                recs[cur] = []
            continue
        if cur and ind == 3:
            mm = re.match(r'(.*?)\s*(\w+)$', rest.split(':')[0].strip())
            if mm:
                recs[cur].append((off, mm.group(1), mm.group(2)))
    return recs, sizes


def sources():
    out = {}
    for d in ['src/main', 'src/game', 'src/menus', 'src/challenge', 'include']:
        for r_, _, fs in os.walk(d):
            for f in fs:
                if f.endswith(('.c', '.h')):
                    p = os.path.join(r_, f)
                    out[p] = open(p, errors='ignore').read()
    return out


TD = r'typedef\s+struct\s*(\w*)\s*\{((?:[^{}]|\{(?:[^{}]|\{[^{}]*\})*\})*)\}\s*%s\s*;[^\n]*\n'


def main():
    args = sys.argv[1:]
    dry = '--dry-run' in args
    args = [a for a in args if a != '--dry-run']
    obj = args[0]
    canon_t = args[args.index('--canon') + 1] if '--canon' in args else None
    src = sources()
    views = {}
    for f, t in src.items():
        if not f.endswith('.c'):
            continue
        for m in re.finditer(r'^\s*extern\s+(?:volatile\s+)?(?:struct\s+)?(\w+)\s+' + re.escape(obj) + r'\s*(?:\[[^\]]*\])?\s*;', t, re.M):
            if m.group(1) not in ('u8', 's8', 'u16', 's16', 'u32', 's32', 'f32'):
                views.setdefault(m.group(1), f)
    lay = {}
    for T, f in views.items():
        P, Ps = dump(f, 'pc')
        G, _ = dump(f, 'gc')
        tag = T
        if T not in P:
            for p, t in src.items():
                m = re.search(TD % re.escape(T), t)
                if m and m.group(1):
                    tag = m.group(1)
                    break
        if P.get(tag) and G.get(tag) and len(P[tag]) == len(G[tag]):
            lay[T] = (f, tag, [(g[0], p[0], p[1], p[2]) for g, p in zip(G[tag], P[tag])], Ps.get(tag))
    if canon_t is None:
        canon_t = max(lay, key=lambda T: len(lay[T][2]))
    cf, _, cmap, csize = lay[canon_t]
    print('canonical: %s (%s), PC size 0x%X' % (canon_t, cf, csize))
    for T, (f, tag, fl, _) in sorted(lay.items()):
        if T == canon_t:
            continue
        exp = {}
        bad = False
        for g, p, ty, name in fl:
            cand = [c for c in cmap if c[0] <= g]
            if not cand:
                continue
            c = max(cand, key=lambda c: c[0])
            exp[name] = c[1] + (g - c[0])
            if exp[name] != p:
                bad = True
        if not bad:
            continue
        # find the typedef (in the file or a header)
        where = None
        for p_, t in src.items():
            m = re.search(TD % re.escape(T), t)
            if m:
                where = (p_, m)
                break
        if where is None:
            print('  %s: typedef not found' % T)
            continue
        p_, m = where
        body = m.group(2)
        fields = []
        ok = True
        for line in body.split('\n'):
            s = re.sub(r'/\*.*?\*/', '', line).split('//')[0].strip()
            if not s:
                continue
            mm = re.match(r'^((?:const\s+|volatile\s+|struct\s+|unsigned\s+)*\w+(?:\s*\([^)]*\))?)\s*((?:\*\s*)*)(\w+)\s*((?:\[[^\]]*\])*)\s*;$', s)
            if not mm:
                ok = False
                print('  %s: cannot parse %r' % (T, s))
                break
            fields.append((mm.group(1), mm.group(2).replace(' ', ''), mm.group(3), mm.group(4)))
        if not ok:
            continue
        members = []
        for ty, stars, name, arr in fields:
            if re.match(r'^(pad|_*unk|_[0-9A-Fa-f]+$)', name) and arr:
                continue  # padding
            if name not in exp:
                if re.match(r'^(pad|_*unk|_[0-9A-Fa-f]+)', name) and arr:
                    continue
                print('  %s.%s: no GameCube offset' % (T, name))
                ok = False
                break
            o = exp[name]
            decl = '%s %s%s%s;' % (ty, stars, name, arr)
            members.append('    struct { %s%s };' % ('u8 _at_%s[0x%X]; ' % (name, o) if o else '', decl))
        if not ok:
            continue
        pcdef = ('typedef union {\n    // PC: each field where %s has it (generated by port/tools/pcview.py %s)\n%s\n    u8 _size[0x%X];\n} %s;\n'
                 % (canon_t, obj, '\n'.join(members), csize, T))
        orig = m.group(0)
        new = '#ifdef TARGET_PC\n' + pcdef + '#else\n' + orig + '#endif\n'
        print('  %s (%s): %d fields' % (T, p_, len(members)))
        if not dry:
            t = src[p_]
            src[p_] = t.replace(orig, new, 1)
            open(p_, 'w').write(src[p_])


main()
