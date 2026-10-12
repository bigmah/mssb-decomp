#!/usr/bin/env python3
"""Helper of tools/gendata.py --unit (run that instead).

gendata_unit.py <unit.c> [--module M] [--sects .data,...] [--skip sym,sym]: print C definitions for
all objects in the unit's split ranges, using gendata.py and the unit's extern declarations.
Objects already defined in the unit are skipped; objects inside a bigger declared object too.
Uninitialised objects are listed in reverse address order (.sbss statics are laid out in reverse
declaration order; .bss follows first reference, see docs/patterns)."""
import re, sys, subprocess, struct, os
HERE = os.path.dirname(os.path.abspath(__file__))
unit = sys.argv[1]
skip = set(sys.argv[sys.argv.index('--skip') + 1].split(',')) if '--skip' in sys.argv else set()
sects = sys.argv[sys.argv.index('--sects') + 1].split(',') if '--sects' in sys.argv else ['.data', '.sdata', '.bss', '.sbss']
module = sys.argv[sys.argv.index('--module') + 1] if '--module' in sys.argv else 'main'
cfg = 'config/GYQE01/' if module == 'main' else 'config/GYQE01/%s/' % module
splits = open(cfg + 'splits.txt').read()
m = re.search(r'^' + re.escape(unit) + r':\n((?:\t.*\n)*)', splits, re.M)
ranges = []
for l in m.group(1).splitlines():
    p = l.split()
    if p[0] in sects:
        ranges.append((p[0], int(p[1][6:], 16), int(p[2][4:], 16)))
syms = []
for l in open(cfg + 'symbols.txt'):
    mm = re.match(r'(\S+) = (\.\w+):0x([0-9A-Fa-f]+);(.*)', l)
    if mm:
        z = re.search(r'size:0x([0-9A-Fa-f]+)', mm.group(4))
        syms.append((mm.group(2), int(mm.group(3), 16), int(z.group(1), 16) if z else 0, mm.group(1)))
pp = subprocess.run(['/usr/bin/clang', '-E', '-P', '-Iinclude', '-Iinclude/stl', '-DNONMATCHING=0', '-w', 'src/' + unit],
                    capture_output=True, text=True).stdout
d = open('orig/GYQE01/sys/main.dol', 'rb').read()
offs = struct.unpack('>18I', d[0:72]); addrs = struct.unpack('>18I', d[72:144]); sizes = struct.unpack('>18I', d[144:216])
def read(a, n):
    if module != 'main': return None
    for i in range(18):
        if addrs[i] <= a and a + n <= addrs[i] + sizes[i]:
            return d[offs[i] + a - addrs[i]: offs[i] + a - addrs[i] + n]
symaddrs = {a for _, a, _, _ in syms}
srctext = open('src/' + unit).read()
for sect, a, b in ranges:
    objs = [(addr, size, name) for s, addr, size, name in syms if s == sect and a <= addr < b
            and not name.startswith(('jumptable_', 'gap_', 'pad_', '@')) and name not in skip]
    objs.sort()
    if sect in ('.bss', '.sbss'): objs.reverse()
    print('// %s 0x%08X..0x%08X%s' % (sect, a, b, ' (reverse address order)' if sect in ('.bss', '.sbss') else ''))
    cover_end = 0
    for addr, size, name in objs:
        if re.search(r'^(?!extern\b)(?!//)(?!#)[A-Za-z_][^;()]*\b' + re.escape(name) + r'\b\s*(\[[^\]]*\]\s*)*(=|;)', srctext, re.M):
            print('// %s is defined above' % name); continue
        if addr < cover_end:
            print('// %s is part of the object above' % name); continue
        if sect in ('.bss', '.sbss'):
            dm = re.search(r'extern\s+([^;]*\b' + re.escape(name) + r'\b[^;]*);', pp)
            if dm and '{' not in dm.group(1):
                print(re.sub(r'\s+', ' ', dm.group(1)).strip() + ';')
            else:
                # look in other units for a declaration
                g = subprocess.run(['grep', '-rhE', r'extern [^;(]*\b' + name + r'\b[^;]*;', 'src'], capture_output=True, text=True).stdout.strip().splitlines()
                if g:
                    print(re.sub(r'^\s*extern\s+', '', g[0].split(';')[0]).strip() + '; // type from another unit')
                else:
                    print('u8 %s[0x%X]; // TODO type' % (name, size))
            continue
        has_decl = re.search(r'extern\s+[^;]*\b' + re.escape(name) + r'\b\s*(?:\[[^\]]*\]\s*)*;', pp)
        extra = []
        other = None
        if not has_decl:
            g = subprocess.run(['grep', '-rhE', r'extern [^;(]*\b' + name + r'\b\s*(\[[^]]*\]\s*)*;', 'src', 'include'],
                               capture_output=True, text=True).stdout.strip().splitlines()
            if g:
                om = re.match(r'\s*extern\s+([^;]*?)\s*\b' + name + r'\b\s*((?:\[[^\]]*\]\s*)*);', g[0])
                if om:
                    r0 = subprocess.run([sys.executable, os.path.join(HERE, 'gendata.py'), 'src/' + unit, name, '--module', module, '--type', om.group(1), '--dims', om.group(2).replace(' ', '')],
                                        capture_output=True, text=True)
                    if r0.stdout.strip(): other = r0
        if other is not None:
            r = other
            has_decl = True
        elif not has_decl:
            data = read(addr, size)
            if data is None and module != 'main' and sect not in ('.bss', '.sbss'):
                extra = ['--type', 'u8', '--dims', '[%d]' % size]
            elif data is None:
                extra = ['--type', 'u8', '--dims', '[0x%X]' % size]
            elif size % 4 == 0 and addr % 4 == 0 and all((w == 0 or w in symaddrs) for w in struct.unpack('>%dI' % (size // 4), data)) and any(struct.unpack('>%dI' % (size // 4), data)):
                extra = ['--type', 'void*', '--dims', '[%d]' % (size // 4)]
            else:
                extra = ['--type', 'u8', '--dims', '[%d]' % size]
        if other is None:
            r = subprocess.run([sys.executable, os.path.join(HERE, 'gendata.py'), 'src/' + unit, name, '--module', module] + extra,
                               capture_output=True, text=True)
        out = r.stdout.strip()
        zm = re.search(r'// SIZE 0x([0-9A-F]+)', r.stderr)
        if zm and int(zm.group(1), 16) > size: cover_end = addr + int(zm.group(1), 16)
        r.stderr = re.sub(r'// SIZE 0x[0-9A-F]+\n?', '', r.stderr)
        if not out:
            out = '// FAILED %s: %s' % (name, r.stderr.strip().splitlines()[-1] if r.stderr.strip() else '?')
        if not has_decl: out += ' // TODO type'
        if r.stderr.strip() and ('NOTE' in r.stderr or 'WARNING' in r.stderr): out += ' ' + ' '.join(r.stderr.strip().splitlines())
        print(out)
    print()
