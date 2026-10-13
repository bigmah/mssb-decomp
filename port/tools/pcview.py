#!/usr/bin/env python3
"""Rewrite the views of a global so their fields land where the canonical view
has them on PC (see port/tools/viewcheck.py).

    python3 port/tools/pcview.py <global> [--canon Type] [--dry-run]

For each view of <global> that viewcheck flags, the typedef gets a PORT_LP64
branch: a union of one-field structs, each field preceded by padding up to
its PC offset (the canonical view's PC offset of the field that covers the
same GameCube offset, plus the distance into it). The GameCube branch keeps
the original typedef. Offsets are numbers: rerun after the canonical struct
changes (viewcheck reports it).
"""
import os, re, subprocess, sys, functools

R = os.getcwd()
PC = ['/usr/bin/clang', '-S', '-emit-llvm', '-o', '/dev/null', '-ferror-limit=0', '-Wno-everything', '-DNDEBUG=1', '-DNONMATCHING=1', '-DTARGET_PC',
      '-DVERNUM=0', '-DVERSION=0', '-Iport/include_game', '-Iport/include', '-Iport/extern/aurora/include', '-Iinclude', '-std=gnu11',
      '-arch', 'arm64', '-fsigned-char', '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=0', '-include', 'port/include/port/prelude.h',
      '-Xclang', '-fdump-record-layouts']
GC = ['/usr/bin/clang', '-target', 'powerpc-unknown-eabi', '-S', '-emit-llvm', '-o', '/dev/null', '-ferror-limit=0', '-nostdinc', '-Iinclude',
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
    if obj == '--type':
        # pcview.py --type Canon@file.c View@file.c ...: views of a struct type
        # (e.g. an array element) rather than of a global.
        canon_t, cfile = args[1].split('@')
        views[canon_t] = cfile
        for a in args[2:]:
            if '@' in a:
                v, vf = a.split('@')
                views[v] = vf
        obj = canon_t
    users = {}  # header -> a .c file that includes it (to lay the view out)
    for f, t in (src.items() if not views else []):
        if f.endswith('.c'):
            for m in re.finditer(r'#include "([^"]+\.h)"', t):
                users.setdefault('include/' + m.group(1), f)
    for f, t in (src.items() if len(views) == 0 else []):
        if f.endswith('.h'):
            if f not in users:
                continue
            for m in re.finditer(r'^\s*extern\s+(?:volatile\s+)?(?:struct\s+)?(\w+)\s+' + re.escape(obj) + r'\s*(?:\[[^\]]*\])?\s*;', t, re.M):
                if m.group(1) not in ('u8', 's8', 'u16', 's16', 'u32', 's32', 'f32'):
                    views.setdefault(m.group(1), users[f])
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
        elif G.get(tag) and re.search(r'PC: each field where \w+ has it[^\n]*\n(?:(?!#endif|typedef)[^\n]*\n)*?\} %s;' % re.escape(T),
                                      ''.join(src.values())):
            # already converted: the GameCube branch gives the fields
            lay[T] = (f, tag, [(g[0], -1, g[1], g[2]) for g in G[tag]], None)
    if canon_t is None:
        canon_t = max(lay, key=lambda T: len(lay[T][2]))
    cf, _, cmap, csize = lay[canon_t]
    print('canonical: %s (%s), PC size 0x%X' % (canon_t, cf, csize))
    CP, CPs = dump(cf, 'pc')
    CG, CGs = dump(cf, 'gc')

    def to_pc(fields_pc, fields_gc, g):
        """PC offset of GameCube offset g in a record, descending into
        struct fields and arrays of structs."""
        best = None
        for (go, _, _), (po, ty, _) in zip(fields_gc, fields_pc):
            if go <= g:
                best = (go, po, ty)
        if best is None:
            return g
        go, po, ty = best
        d = g - go
        # arrays of pointers: 4-byte elements on GameCube, 8 on PC
        pm = re.match(r'^.*\*\s*((?:\[\d+\])+)$', ty.strip())
        if pm and d >= 4:
            return po + (d // 4) * 8 + d % 4
        m = re.match(r'^(?:struct |union )?(\w+)(?: ?\[(\d+)\])*$', ty.strip())
        if m and m.group(1) in CP and m.group(1) in CG and len(CP[m.group(1)]) == len(CG[m.group(1)]):
            el = m.group(1)
            if '[' in ty:
                gsz, psz = CGs.get(el), CPs.get(el)
                if gsz and psz:
                    return po + (d // gsz) * psz + to_pc(CP[el], CG[el], d % gsz)
            else:
                return po + to_pc(CP[el], CG[el], d)
        return po + d
    for T, (f, tag, fl, _) in sorted(lay.items()):
        if T == canon_t:
            continue
        exp = {}
        bad = False
        for g, p, ty, name in fl:
            if not any(c[0] <= g for c in cmap):
                continue
            exp[name] = to_pc(CP[lay[canon_t][1]], CG[lay[canon_t][1]], g)
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
        old_pc = None
        if where is not None:
            g = re.search(r'#ifdef (?:TARGET_PC|PORT_LP64[^\n]*)\ntypedef union \{\n    // PC: each field where [^\n]*\n(?:(?!#endif|typedef)[^\n]*\n)*?\} %s;\n#else\n' % re.escape(T),
                          src[where[0]])
            if g:
                old_pc = g.group(0)
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
            fp = re.match(r'^(.+?)\(\s*\*\s*(\w+)\s*\)\s*(\(.*\))\s*;$', s)
            if fp:  # function pointer: keep the declaration as written
                fields.append(('', '', fp.group(2), None, s))
                continue
            mm = re.match(r'^((?:const\s+|volatile\s+|struct\s+|unsigned\s+)*\w+(?:\s*\([^)]*\))?)\s*((?:\*\s*)*)(\w+)\s*((?:\[[^\]]*\])*)\s*;$', s)
            if not mm:
                ok = False
                print('  %s: cannot parse %r' % (T, s))
                break
            fields.append((mm.group(1), mm.group(2).replace(' ', ''), mm.group(3), mm.group(4), None))
        if not ok:
            continue
        members = []
        for ty, stars, name, arr, raw in fields:
            if name not in exp:
                if arr and re.match(r'^(pad|_*unk|_[0-9A-Fa-f]+)', name):
                    continue
                print('  %s.%s: no GameCube offset' % (T, name))
                ok = False
                break
            o = exp[name]
            decl = raw if raw else '%s %s%s%s;' % (ty, stars, name, arr)
            members.append('    struct { %s%s };' % ('u8 _at_%s[0x%X]; ' % (name, o) if o else '', decl))
        if not ok:
            continue
        pcdef = ('typedef union {\n    // PC: each field where %s has it (generated by port/tools/pcview.py %s)\n%s\n    u8 _size[0x%X];\n} %s;\n'
                 % (canon_t, obj, '\n'.join(members), csize, T))
        orig = m.group(0)
        print('  %s (%s): %d fields%s' % (T, p_, len(members), ' (regenerated)' if old_pc else ''))
        if not dry:
            t = src[p_]
            if old_pc:
                t = t.replace(old_pc, '#ifdef PORT_LP64 // offsets for 64-bit pointers (wasm32 uses the GameCube layout)\n' + pcdef + '#else\n', 1)
            else:
                t = t.replace(orig, '#ifdef PORT_LP64 // offsets for 64-bit pointers (wasm32 uses the GameCube layout)\n' + pcdef + '#else\n' + orig + '#endif\n', 1)
            src[p_] = t
            open(p_, 'w').write(t)


if __name__ == '__main__':
    main()
