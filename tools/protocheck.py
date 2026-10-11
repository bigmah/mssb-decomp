#!/usr/bin/env python3
"""Cross-TU prototype consistency check.

Runs clang -ast-dump=json on every TU in compile_commands.json (with
-DNONMATCHING=1, as the port builds it), collects every FunctionDecl
(definitions, header prototypes, block-scope/local externs, implicit decls),
and compares every declaration of an external function against its
definition.

Classes:
  ABI    : param count, or a param/return differs in its 64-bit/wasm class
           (void / i32 / long / i64 / f32 / f64 / ptr / struct)
  noproto: declared `f()` (unprototyped) but defined with params
  strict : canonical types differ, but same ABI class (e.g. u8 vs s32)

Usage: protocheck.py [ROOT] [--json out.json] [--strict] [--module M] [-v]
"""
import json, os, re, subprocess, sys, collections
from concurrent.futures import ThreadPoolExecutor

args = sys.argv[1:]
root = os.getcwd()
if args and not args[0].startswith('-'):
    root = os.path.abspath(args.pop(0))
show_strict = '--strict' in args
verbose = '-v' in args
only_mod = None
if '--module' in args:
    only_mod = args[args.index('--module') + 1]
jout = args[args.index('--json') + 1] if '--json' in args else None

cc = json.load(open(os.path.join(root, 'compile_commands.json')))

def module_of(path):
    rel = os.path.relpath(path, root)
    p = rel.split('/')
    if p[0] == 'src' and len(p) > 1:
        if p[1] in ('game', 'menus', 'challenge'):
            return p[1]
        if p[1] in ('Dolphin', 'Musyx'):
            return 'sdk'
        return 'main'
    return 'hdr'

def run(entry):
    a = [x for x in entry['arguments'] if x not in ('-c',)]
    out = []
    skip = False
    for x in a:
        if skip:
            skip = False
            continue
        if x == '-o':
            skip = True
            continue
        out.append(x)
    if not os.path.exists(entry['file']):
        return entry['file'], None, []
    cmd = out + ['-DNONMATCHING=1', '-fsyntax-only', '-ferror-limit=0', '-w',
                 '-Werror=int-conversion', '-Werror=incompatible-function-pointer-types',
                 '-Xclang', '-ast-dump=json']
    p = subprocess.run(cmd, cwd=entry['directory'], capture_output=True, text=True)
    try:
        ast = json.loads(p.stdout)
    except Exception:
        ast = None
    errs = [l for l in p.stderr.splitlines() if ' error: ' in l]
    return entry['file'], ast, errs

def ret_of(qt):
    # strip trailing balanced (...) group
    if not qt.endswith(')'):
        return qt
    depth = 0
    for i in range(len(qt) - 1, -1, -1):
        c = qt[i]
        if c == ')':
            depth += 1
        elif c == '(':
            depth -= 1
            if depth == 0:
                r = qt[:i].strip()
                return 'void *' if '(*' in r else r  # function returning a function pointer
    return qt

typedefs = {}

def abi(t, depth=0):
    t = t.replace('const ', '').replace('volatile ', '').strip()
    if depth < 10 and re.fullmatch(r'\w+', t) and t in typedefs:
        return abi(typedefs[t], depth + 1)
    if '*' in t or '[' in t or '(' in t:
        return 'ptr'
    if t == 'void':
        return 'void'
    if t == 'float':
        return 'f32'
    if t in ('double', 'long double'):
        return 'f64'
    if 'long long' in t:
        return 'i64'
    if re.search(r'\blong\b', t):
        return 'i32'  # port maps s32/long to int
    if t.startswith('struct ') or t.startswith('union '):
        return 'struct'
    return 'i32'

def canon(node_type):
    return node_type.get('desugaredQualType', node_type.get('qualType'))

def norm_struct(t):
    # anonymous struct spellings differ per TU; normalize
    return re.sub(r'\(unnamed [^)]*\)|\(anonymous [^)]*\)', '(anon)', t)

decls = collections.defaultdict(list)   # name -> list of dict
errors = {}

def track(l, st):
    """clang JSON omits file/line when unchanged from the previous location
    written; replay in emission order. Returns (file, line) of this loc."""
    if not l:
        return None
    if 'spellingLoc' in l or 'expansionLoc' in l:
        track(l.get('spellingLoc'), st)
        return track(l.get('expansionLoc'), st)
    if 'file' in l:
        st[0] = l['file']
    if 'line' in l:
        st[1] = l['line']
    return (st[0], st[1])

def walk(node, tu, in_func, st):
    fl = track(node.get('loc'), st)
    r = node.get('range') or {}
    fb = track(r.get('begin'), st)
    track(r.get('end'), st)
    f, line = fl if fl else (fb if fb else (None, None))
    k = node.get('kind')
    if k == 'CStyleCastExpr' and node.get('castKind') in ('PointerToIntegral', 'IntegralToPointer') and in_func:
        src = node.get('inner', [{}])[0]
        while src.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and src.get('inner'):
            src = src['inner'][0]
        if src.get('kind') not in ('IntegerLiteral',):
            casts.append(dict(tu=tu, file=f, line=line, kind=node['castKind'],
                              to=node['type']['qualType']))
    if k == 'CallExpr' and node.get('inner'):
        callee = node['inner'][0]
        while callee.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and callee.get('inner'):
            if callee.get('kind') == 'ParenExpr' or callee.get('castKind') != 'FunctionToPointerDecay':
                callee = callee['inner'][0]
            else:
                break
        if callee.get('kind') == 'CStyleCastExpr':
            s = callee.get('inner', [{}])[0]
            while s.get('kind') in ('ParenExpr', 'ImplicitCastExpr') and s.get('inner'):
                s = s['inner'][0]
            if s.get('kind') == 'DeclRefExpr' and (s.get('referencedDecl') or {}).get('kind') == 'FunctionDecl':
                castcalls.append(dict(tu=tu, file=f, line=line, name=s['referencedDecl']['name'],
                                      to=callee['type']['qualType']))
    if node.get('kind') == 'TypedefDecl' and 'name' in node:
        typedefs.setdefault(node['name'], canon(node['type']))
    if node.get('kind') == 'FunctionDecl' and 'name' in node:
        inner = node.get('inner', [])
        params = [canon(c['type']) for c in inner if c.get('kind') == 'ParmVarDecl']
        is_def = any(c.get('kind') == 'CompoundStmt' for c in inner)
        qt = node['type']['qualType']
        cq = canon(node['type'])
        noproto = bool(re.search(r'\(\)$', qt)) and not re.search(r'\(void\)$', qt)
        decls[node['name']].append(dict(
            tu=tu, file=f, line=line, is_def=is_def,
            static=node.get('storageClass') == 'static',
            implicit=bool(node.get('isImplicit')),
            local=in_func, ret=ret_of(cq), params=params, qt=qt,
            noproto=noproto, variadic='...' in qt))
        for c in inner:
            walk(c, tu, True, st)
        return
    for c in node.get('inner', []) or []:
        walk(c, tu, in_func, st)

casts = []
castcalls = []
with ThreadPoolExecutor(max_workers=os.cpu_count()) as ex:
    for tu, ast, errs in ex.map(run, cc):
        if errs:
            errors[tu] = errs
        if ast:
            walk(ast, tu, False, [None, None])

def sig_abi(d):
    return (abi(d['ret']), tuple(abi(p) for p in d['params']))

def sig_strict(d):
    return (norm_struct(d['ret']), tuple(norm_struct(p) for p in d['params']))

def rel(p):
    return os.path.relpath(p, root) if p else '?'

problems = []
for name, ds in decls.items():
    if name.startswith('__builtin'):
        continue
    defs = [d for d in ds if d['is_def'] and not d['static']]
    if not defs:
        continue
    # dedupe defs (same file/line)
    df = defs[0]
    mod = module_of(df['tu'])
    seen = set()
    for d in ds:
        if d['is_def'] or d['static']:
            continue
        if not os.path.exists(os.path.join(root, d['tu'])) and not os.path.exists(d['tu']):
            continue
        key = ((d['file'] or '').lower(), d['line'], d['qt'], d['tu'] if d['file'] in (None, '<scratch space>') else '')
        if key in seen:
            continue
        seen.add(key)
        kind = None
        if d['noproto'] and df['params']:
            kind = 'noproto'
        elif d['implicit']:
            kind = 'implicit'
        elif d['noproto']:
            continue
        elif len(d['params']) != len(df['params']) or sig_abi(d) != sig_abi(df):
            kind = 'ABI'
        elif sig_strict(d) != sig_strict(df):
            kind = 'strict'
        if kind:
            problems.append(dict(kind=kind, name=name, module=mod,
                                 decl=f"{rel(d['file']) if d['file'] not in (None, '<scratch space>') else rel(d['tu']) + '(macro)'}:{d['line']}", decl_qt=d['qt'],
                                 local=d['local'], used_in=rel(d['tu']),
                                 defn=f"{rel(df['file'])}:{df['line']}", def_qt=df['qt']))

# multiple non-static definitions of same name with differing ABI (duplicate defs)
for name, ds in decls.items():
    defs = {}
    for d in ds:
        if d['is_def'] and not d['static']:
            defs[(d['file'], d['line'])] = d
    if len(defs) > 1:
        sigs = set(sig_abi(d) for d in defs.values())
        if len(sigs) > 1:
            d0 = list(defs.values())
            problems.append(dict(kind='dupdef', name=name, module=module_of(d0[0]['tu']),
                                 decl=' / '.join(f"{rel(d['file'])}:{d['line']}" for d in d0),
                                 decl_qt=' / '.join(d['qt'] for d in d0), local=False,
                                 used_in='', defn='', def_qt=''))

# group by (name, decl location) for the count
cnt = collections.Counter()
for p in problems:
    if p['kind'] == 'strict' and not show_strict:
        continue
    cnt[(p['module'], p['kind'])] += 1

mods = sorted(set(m for m, _ in cnt))
print('per module:')
for m in mods:
    print(f"  {m:10s} " + '  '.join(f"{k}={cnt[(m, k)]}" for k in ('ABI', 'noproto', 'implicit', 'dupdef', 'strict') if cnt[(m, k)]))
print(f"  TOTAL ABI={sum(v for (m,k),v in cnt.items() if k=='ABI')} "
      f"noproto={sum(v for (m,k),v in cnt.items() if k=='noproto')} "
      f"implicit={sum(v for (m,k),v in cnt.items() if k=='implicit')} "
      f"strict={sum(v for (m,k),v in cnt.items() if k=='strict')}")
print(f"TUs with clang errors: {len(errors)}")
ec = collections.Counter()
for tu, es in errors.items():
    m = module_of(tu)
    for e in es:
        if 'conflicting types' in e: ec[(m, 'conflict')] += 1
        elif '-Wint-conversion' in e: ec[(m, 'intconv')] += 1
        elif 'incompatible-function-pointer' in e: ec[(m, 'fnptr')] += 1
        elif 'undeclared function' in e:
            fn = re.search(r"function '([^']*)'", e).group(1)
            ec[(m, 'intrinsic' if fn.startswith('__') else 'undeclared')] += 1
        elif 'no such file' in e or 'no input' in e: pass
        else: ec[(m, 'other')] += 1
print('clang errors per TU module: ' + ', '.join(f"{m}/{k}={v}" for (m, k), v in sorted(ec.items())))
# dedupe casts by (file, line, kind)
cu = {}
for c in casts:
    cu[(c['file'], c['line'], c['kind'])] = c
cc_ = collections.Counter((module_of(c['tu']) if c['file'] and '/src/' in c['file'] else module_of(c['tu']), c['kind']) for c in cu.values())
print('pointer<->int casts per module: ' + ', '.join(f"{m}/{'p2i' if k == 'PointerToIntegral' else 'i2p'}={v}" for (m, k), v in sorted(cc_.items())))
cq = {}
for c in castcalls:
    cq[(c['file'], c['line'], c['name'])] = c
def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([': depth += 1
        if ch in ')]': depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip() and cur.strip() != 'void':
        out.append(cur.strip())
    return out
def fnptr_sig(t):
    # "R (*)(P1, P2)"
    m = re.match(r'^(.*?)\s*\(\*\)\((.*)\)$', t)
    if not m:
        return None
    return (abi(m.group(1)), tuple(abi(p) for p in split_params(m.group(2))))
for c in cq.values():
    ds = [d for d in decls.get(c['name'], []) if d['is_def']]
    c['abi_ok'] = None
    if ds:
        c['def_qt'] = ds[0]['qt']
        c['abi_ok'] = fnptr_sig(c['to']) == sig_abi(ds[0])
ccc = collections.Counter((module_of(c['tu']), c['abi_ok']) for c in cq.values())
print('calls through function casts per module (ABI-mismatch / same-ABI / no def): ' + ', '.join(
    f"{m}={ccc[(m, False)]}/{ccc[(m, True)]}/{ccc[(m, None)]}" for m in sorted(set(m for m, _ in ccc))))
if verbose:
    for tu, e in sorted(errors.items()):
        print('ERR', rel(tu), len(e))
        for l in e[:5]:
            print('   ', l)

for p in sorted(problems, key=lambda p: (p['module'], p['kind'], p['name'])):
    if p['kind'] == 'strict' and not show_strict:
        continue
    if only_mod and p['module'] != only_mod:
        continue
    print(f"{p['kind']:8s} {p['name']:28s} decl {p['decl']} {'(local)' if p['local'] else ''}\n"
          f"           {p['decl_qt']}\n         def {p['defn']}\n           {p['def_qt']}")

if jout:
    json.dump(dict(problems=problems, errors=errors, casts=list(cu.values()), castcalls=list(cq.values())),
              open(jout, 'w'), indent=1)
