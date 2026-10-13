#!/usr/bin/env python3
"""Check that globals declared with several struct types ("views") agree on PC.

    python3 port/tools/viewcheck.py            # from the repo root

For each global the game sources declare with more than one struct type (one
of which holds pointers), the view with the most fields is canonical. Every
field of the other views is placed by its GameCube offset (clang
powerpc-eabi layout) and must land at the PC offset the canonical view gives
(clang arm64 layout, port flags). Mismatches are usually padding arrays sized
for 4-byte pointers. "no layout": clang never laid the view out (unused, or
an anonymous struct), so it isn't checked.
"""
# globals declared with several struct types: flag the ones whose views contain pointers
import re,os,collections
src={}
for d in ['src/main','src/game','src/menus','src/challenge','include','src/C3','src/Unknown']:
    for r,_,fs in os.walk(d):
        for f in fs:
            if f.endswith(('.c','.h')): p=os.path.join(r,f); src[p]=open(p,errors='ignore').read()
IDX={}
for p,t in src.items():
    for m in re.finditer(r'typedef\s+(?:struct|union)\s*\w*\s*\{((?:[^{}]|\{(?:[^{}]|\{[^{}]*\})*\})*)\}\s*(\w+)\s*;',t,re.S):
        IDX.setdefault(m.group(2),m.group(1))
def has_ptr(t,depth=0,seen=None):
    b=IDX.get(t)
    if b is None or depth>4: return False
    b=re.sub(r'/\*.*?\*/|//[^\n]*','',b,flags=re.S)
    if re.search(r'\*|\(\s*\*',b): return True
    for m in re.finditer(r'^\s*(?:struct\s+)?(\w+)\s+\w',b,re.M):
        if m.group(1) in IDX and m.group(1)!=t and has_ptr(m.group(1),depth+1): return True
    return False
OBJS=[]
views=collections.defaultdict(set)
for p,t in src.items():
    for m in re.finditer(r'^\s*extern\s+(?:volatile\s+)?(?:struct\s+)?(\w+)\s+(\w+)\s*(?:\[[^\]]*\])?\s*;',t,re.M):
        views[m.group(2)].add((m.group(1),p))
    for m in re.finditer(r'^(?:static\s+)?(?:struct\s+)?(\w+)\s+(\w+)\s*(?:\[[^\]]*\])?\s*(?:=|;)',t,re.M):
        if m.group(1) in IDX: views[m.group(2)].add((m.group(1),p))
for n,vs in sorted(views.items()):
    types={t for t,_ in vs}
    if len(types)<2: continue
    ptr=[t for t in types if has_ptr(t)]
    if ptr: OBJS.append(n)

# For globals declared with several struct types (views), check that every
# view field lands at the same place on PC as in the canonical view, given the
# GameCube offsets (clang powerpc-eabi layout) of both.
import subprocess,sys,functools,concurrent.futures as cf
R=os.getcwd()
PC=['/usr/bin/clang','-S', '-emit-llvm', '-o', '/dev/null','-ferror-limit=0','-Wno-everything','-DNDEBUG=1','-DNONMATCHING=1','-DTARGET_PC','-DVERNUM=0','-DVERSION=0',
    '-Iport/include','-Iport/extern/aurora/include','-Iinclude','-std=gnu11','-arch','arm64','-fsigned-char','-U_FORTIFY_SOURCE','-D_FORTIFY_SOURCE=0',
    '-include','port/include/port/prelude.h','-Xclang','-fdump-record-layouts']
GC=['/usr/bin/clang','-target','powerpc-unknown-eabi','-S', '-emit-llvm', '-o', '/dev/null','-ferror-limit=0','-nostdinc','-Iinclude','-Iinclude/stl','-DNONMATCHING=1','-fsigned-char',
    '-Wno-everything','-Xclang','-fdump-record-layouts']
if os.path.isdir('port/include_game'): PC.insert(PC.index('-Iport/include'),'-Iport/include_game')
@functools.lru_cache(None)
def dump(f,plat):
    r=subprocess.run((PC if plat=='pc' else GC)+[f],capture_output=True,text=True,cwd=R)
    recs={}; cur=None
    for l in r.stdout.split('\n'):
        m=re.match(r'\s*(\d+) \|( *)(.*)$',l)
        if l.startswith('*** Dumping AST Record Layout'): cur=None; continue
        if not m: continue
        off,ind,rest=int(m.group(1)),len(m.group(2)),m.group(3)
        if ind==1:
            mm=re.match(r'(?:struct|union) (\w+)',rest); cur=None
            if mm and mm.group(1) not in recs: cur=mm.group(1); recs[cur]=[]
            continue
        if cur and ind==3:
            mm=re.match(r'(.*?)\s*(\w+)$',rest.split(':')[0].strip()) if True else None
            if mm: recs[cur].append((off,mm.group(1),mm.group(2)))
    return recs
def typedef_tag(f,t):
    s=open(f,errors='ignore').read()
    return t
src={}
for d in ['src/main','src/game','src/menus','src/challenge','src/C3','src/Unknown']:
    for r_,_,fs in os.walk(d):
        for f in fs:
            if f.endswith('.c'): src[os.path.join(r_,f)]=open(os.path.join(r_,f),errors='ignore').read()
# typedef name -> struct tag (dumps show tags)
tags={}
for d in ['src','include']:
    for r_,_,fs in os.walk(d):
        for f in fs:
            if f.endswith(('.c','.h')):
                t=open(os.path.join(r_,f),errors='ignore').read()
                for m in re.finditer(r'typedef\s+struct\s+(\w+)\s*\{(?:[^{}]|\{(?:[^{}]|\{[^{}]*\})*\})*\}\s*(\w+)\s*;',t): tags.setdefault(m.group(2),m.group(1))
objs=OBJS
def check(o):
    out=[]
    views={}
    for f,t in src.items():
        for m in re.finditer(r'^\s*extern\s+(?:volatile\s+)?(?:struct\s+)?(\w+)\s+'+re.escape(o)+r'\s*(?:\[[^\]]*\])?\s*;',t,re.M):
            T=m.group(1)
            if T in ('u8','s8','u16','s16','u32','s32','f32'): continue
            views.setdefault(T,f)
    lay={}
    for T,f in views.items():
        tag=tags.get(T,T)
        p=dump(f,'pc'); g=dump(f,'gc')
        P=p.get(tag) or p.get(T); G=g.get(tag) or g.get(T)
        if P and G and len(P)==len(G): lay[T]=(f,[(gg[0],pp[0],pp[1],pp[2]) for gg,pp in zip(G,P)])
        else: out.append('%s: view %s (%s): no layout (pc %s gc %s)'%(o,T,f,bool(P),bool(G)))
    if len(lay)<2: return out
    canon=max(lay,key=lambda T:len(lay[T][1]))
    cmap=lay[canon][1]
    for T,(f,fl) in lay.items():
        if T==canon: continue
        for g,p,ty,name in fl:
            if re.match(r'^(pad|_*unk|_[0-9A-Fa-f]+$)',name) and '[' in ty: continue
            cand=[c for c in cmap if c[0]<=g]
            if not cand: continue
            c=max(cand,key=lambda c:c[0])
            exp=c[1]+(g-c[0])
            if exp!=p:
                out.append('%s: %s.%s (%s) gc 0x%X pc 0x%X, but %s.%s is at pc 0x%X -> expected 0x%X'%(o,T,name,f,g,p,canon,c[3],c[1],exp))
    return out
with cf.ThreadPoolExecutor(8) as ex:
    for res in ex.map(check,objs):
        for l in res: print(l)
