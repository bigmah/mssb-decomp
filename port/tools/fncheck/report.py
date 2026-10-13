#!/usr/bin/env python3
"""List indirect calls that would trap in wasm, from MSSB_SANITIZE_FUNCTION runs.

    python3 port/tools/fncheck/report.py build/fsruns/*.fn

Each line of a log is a call through a function pointer whose C type differs
from the callee's; this keeps the ones whose wasm signatures (i32/i64/f32/f64
params, void or value return) differ too. Run from the repo root.
"""
# filt.py logs... : UBSan function-type reports that differ at the wasm level
import re,os,sys,collections
sys.path.insert(0,os.path.dirname(__file__))
src={}
for d in ['src/main','src/game','src/menus','src/challenge','src/C3','src/Unknown','port/gen','port/game']:
    for r,_,fs in os.walk(d):
        for f in fs:
            if f.endswith('.c'): src[os.path.join(r,f)]=open(os.path.join(r,f),errors='ignore').read()
defs={}
for p,t in src.items():
    for m in re.finditer(r'^(?:static\s+)?(?:inline\s+)?([A-Za-z_][\w \*]*?)\s*\b(\w+)\s*\(([^;{)]*)\)\s*\{',t,re.M):
        ret,name,params=m.group(1).strip(),m.group(2),m.group(3).strip()
        if name in ('if','while','for','switch'): continue
        defs.setdefault(name,(ret,params,p))
def w(t):
    t=t.replace('const','').replace('volatile','').strip()
    if '*' in t or '[' in t or '(' in t: return 'i32'
    if re.search(r'\b(f32|float)\b',t): return 'f32'
    if re.search(r'\b(f64|double)\b',t): return 'f64'
    if re.search(r'\b(s64|u64|OSTime|long long)\b',t): return 'i64'
    if re.search(r'\b(Vec|V3i|struct)\b',t) and '*' not in t: return 'i32'  # byval aggregate
    return 'i32'
def split_params(s):
    out=[];depth=0;cur=''
    for ch in s:
        if ch=='(' : depth+=1
        if ch==')': depth-=1
        if ch==',' and depth==0: out.append(cur); cur=''
        else: cur+=ch
    if cur.strip(): out.append(cur)
    return [x.strip() for x in out if x.strip() not in ('void','')]
def def_sig(n):
    if n not in defs: return None
    ret,params,p=defs[n]
    r='v' if (ret.split()[-1]=='void' and '*' not in ret) else w(ret)
    return r+'('+','.join(w(x) for x in split_params(params))+')'
def type_sig(t):
    m=re.match(r'(.*?)\(\*\)\((.*)\)$',t.strip())
    if not m: return None
    ret,params=m.group(1).strip(),m.group(2)
    r='v' if ret=='void' else w(ret)
    return r+'('+','.join(w(x) for x in split_params(params))+')'
seen=collections.OrderedDict()
for f in sys.argv[1:]:
    for l in open(f,errors='ignore'):
        m=re.search(r"fncheck (\S+\.c:\d+) callee (\S+) type '(.*)'",l)
        if not m:
            m=re.search(r"(\S+\.c:\d+):\d+: runtime error: call to function (\w+) through pointer to incorrect function type '(.*)'",l)
        if not m: continue
        site,fn,typ=m.groups(); typ=typ.strip("'")
        a,b=def_sig(fn),type_sig(typ)
        if a is not None and a==b: continue
        site=site.split('/p6-y/')[-1]
        seen[(site,fn)]=(a,b,typ)
for (site,fn),(a,b,typ) in sorted(seen.items()): print(f'{site}  {fn}: def {a}  call {b}   [{typ}]')
