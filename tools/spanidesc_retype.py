#!/usr/bin/env python3
"""Retype `extern u8 x[];` sprite tables that a source file passes to fn_80034E20 as SpaniDesc arrays.

    tools/spanidesc_retype.py src/game/rep_3448.c [--module game]

Sizes come from symbols.txt (must be a multiple of 0x20). Adds #include "main/SpaniDesc.h".
Run before tools/adddata.py so gendata emits SpaniDesc initialisers.
"""
import re, sys
src = sys.argv[1]
module = sys.argv[sys.argv.index('--module') + 1] if '--module' in sys.argv else 'game'
sizes = {}
for l in open('config/GYQE01/%s/symbols.txt' % module):
    m = re.match(r'^(\S+) = \.data:0x\w+; // type:object size:0x([0-9A-Fa-f]+)', l)
    if m: sizes[m.group(1)] = int(m.group(2), 16)
s = open(src).read()
names = set(re.findall(r'fn_80034E20\([^,]+,\s*(lbl_\d_data_\w+)\)', s))
done = []
for n in sorted(names):
    sz = sizes.get(n)
    if not sz or sz % 0x20: continue
    s2 = re.sub(r'^extern\s+u8\s+' + n + r'\s*\[[^\]]*\]\s*;', 'extern SpaniDesc %s[%d];' % (n, sz // 0x20), s, flags=re.M)
    if s2 != s:
        done.append(n); s = s2
        # other uses keep byte arithmetic: name + 2 -> ((u8*)name + 2)
        out = []
        for line in s.split('\n'):
            if line.lstrip().startswith(('extern', '//')) or re.search(r'fn_80034E20\([^,]+,\s*' + n + r'\)', line):
                out.append(line); continue
            out.append(re.sub(r'(?<!\(u8\*\))(?<!\w)' + n + r'\b', '((u8*)%s)' % n, line))
        s = '\n'.join(out)
if done and 'main/SpaniDesc.h' not in s:
    first = re.search(r'^#include [^\n]*\n', s, re.M)
    s = s[:first.end()] + '#include "main/SpaniDesc.h"\n' + s[first.end():]
open(src, 'w').write(s)
print('retyped', done)
