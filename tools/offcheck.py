#!/usr/bin/env python3
"""Check the /*0xNNN*/ field comments and "} T; // size: 0xNNN" comments in headers
against the real layout (clang, PowerPC 32-bit EABI, which lays structs out like MWCC
with -enum int). Offsets inside a named nested struct may be relative or absolute.

    python3 tools/offcheck.py                       # include/game/*.h
    python3 tools/offcheck.py include/main/foo.h [...]

Needs clang on PATH. Prints one line per mismatch; exit status 1 if any.
"""
import re, subprocess, sys, os, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OFF_RE = re.compile(r'/\*\s*(0x[0-9A-Fa-f]+)\s*\*/')


def strip_comments_keep_offsets(text):
    # replace offset comments by a marker, drop the other comments
    text = re.sub(r'\bE\(\s*([^,()]+?)\s*,[^()]*\)', r'\1', text)
    text = OFF_RE.sub(lambda m: f' @OFF{m.group(1)}@ ', text)
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', '', text)
    text = re.sub(r'^\s*#[^\n]*(\\\n[^\n]*)*', '', text, flags=re.M)
    return text


def parse(text):
    """Yield (type_expr, field_path, offset, relative_to_path) checks."""
    toks = re.findall(r'@OFF0x[0-9A-Fa-f]+@|[A-Za-z_]\w*|\d+\w*|[{};,()\[\]*:=]|\S', text)
    checks = []
    i = 0
    n = len(toks)

    def parse_body(j):
        """parse from after '{' to matching '}'; returns (fields, j after '}')
        fields: list of (kind, data): ('f', name, off) or ('sub', name|None, fields)"""
        fields = []
        pend_off = None
        decl = []
        while j < n:
            t = toks[j]
            if t.startswith('@OFF'):
                pend_off = int(t[4:-1], 16); j += 1; continue
            if t == '}':
                return fields, j + 1
            if t in ('struct', 'union') and (toks[j + 1] == '{' or (j + 2 < n and toks[j + 2] == '{')):
                k = j + 1 if toks[j + 1] == '{' else j + 2
                sub, k = parse_body(k + 1)
                # name after '}'
                name = None
                if toks[k] != ';':
                    name = toks[k]
                    while toks[k] != ';':
                        k += 1
                fields.append(('sub', name, sub, pend_off))
                pend_off = None
                decl = []
                j = k + 1
                continue
            if t == ';':
                if pend_off is not None and decl:
                    name = field_name(decl)
                    if name:
                        fields.append(('f', name, pend_off))
                pend_off = None
                decl = []
                j += 1
                continue
            decl.append(t)
            j += 1
        return fields, j

    while i < n:
        t = toks[i]
        if t in ('struct', 'union') and i + 1 < n:
            typedef = i > 0 and toks[i - 1] == 'typedef'
            k = i + 1
            tag = None
            if toks[k] != '{':
                tag = toks[k]; k += 1
            if k < n and toks[k] == '{':
                fields, k = parse_body(k + 1)
                tname = None
                if typedef and k < n and re.match(r'[A-Za-z_]\w*$', toks[k]):
                    tname = toks[k]
                elif tag:
                    tname = f'{t} {tag}'
                if tname:
                    emit(tname, fields, '', 0, checks)
                i = k
                continue
        i += 1
    return checks


def field_name(decl):
    if ':' in decl:  # bitfield
        return None
    if '(' in decl:  # function pointer: (*name)
        for a, b in zip(decl, decl[1:]):
            if a == '*' and re.match(r'[A-Za-z_]\w*$', b):
                return b
        return None
    if '=' in decl:
        return None
    # cut at first '[' or ','
    out = []
    for x in decl:
        if x in ('[', ','):
            break
        out.append(x)
    if out and re.match(r'[A-Za-z_]\w*$', out[-1]) and len(out) >= 2:
        return out[-1]
    return None


def emit(tname, fields, prefix, base_is_named, checks):
    for f in fields:
        if f[0] == 'f':
            checks.append((tname, prefix + f[1], f[2], prefix.rstrip('.') if base_is_named else None))
        else:
            _, name, sub, off = f
            if name:
                if off is not None:
                    checks.append((tname, prefix + name, off, prefix.rstrip('.') if base_is_named else None))
                emit(tname, sub, prefix + name + '.', 1, checks)
            else:
                emit(tname, sub, prefix, base_is_named, checks)


def run(hdr):
    text = open(os.path.join(ROOT, hdr)).read()
    checks = parse(strip_comments_keep_offsets(text))
    sizes = [(m.group(1), int(m.group(2), 16)) for m in
             re.finditer(r'^\}\s*(\w+)\s*;\s*//\s*size:?\s*(0x[0-9A-Fa-f]+)\b', text, re.M)]
    if not checks and not sizes:
        return None
    inc = hdr[len('include/'):] if hdr.startswith('include/') else hdr
    lines = []
    if '_MUSYX_MUSYX' in text:
        lines.append('#include "musyx/musyx.h"')
    lines.append(f'#include "{inc}"')
    for idx, (t, size) in enumerate(sizes):
        lines.append(f'_Static_assert(sizeof({t}) == {size}, "SIZ{idx}");')
    for idx, (t, path, off, rel) in enumerate(checks):
        expr = f'__builtin_offsetof({t}, {path})'
        if rel:
            expr = f'({expr} - __builtin_offsetof({t}, {rel}))'
            # accept absolute too
            lines.append(f'_Static_assert({expr} == {off} || __builtin_offsetof({t}, {path}) == {off}, "CHK{idx}");')
        else:
            lines.append(f'_Static_assert({expr} == {off}, "CHK{idx}");')
    with tempfile.NamedTemporaryFile('w', suffix='.c', delete=False) as tf:
        tf.write('\n'.join(lines) + '\n')
        path = tf.name
    r = subprocess.run(['clang', '-target', 'powerpc-unknown-eabi', '-fsyntax-only', '-w', '-ferror-limit=0',
                        '-fms-extensions', '-std=gnu11', '-I', os.path.join(ROOT, 'include'),
                        '-I', os.path.join(ROOT, 'include/stl'), '-DNONMATCHING=0', path],
                       capture_output=True, text=True)
    os.unlink(path)
    bad = []
    errs = r.stderr
    for m in re.finditer(r'static assertion failed[^\n]*SIZ(\d+)[^\n]*\n(?:.*\n){0,4}?.*expression evaluates to \'([^\']*)\'', errs):
        t, size = sizes[int(m.group(1))]
        bad.append(((t, 'sizeof', size, None), m.group(2)))
    for m in re.finditer(r'static assertion failed[^\n]*CHK(\d+)[^\n]*\n(?:.*\n){0,4}?.*expression evaluates to \'([^\']*)\'', errs):
        idx = int(m.group(1))
        bad.append((checks[idx], m.group(2)))
    failed_ids = set(int(x) for x in re.findall(r'CHK(\d+)', errs))
    other = [l for l in errs.splitlines() if 'error' in l and 'CHK' not in l and 'SIZ' not in l
             and 'errors generated' not in l and 'error generated' not in l]
    for idx in failed_ids - set(checks.index(b[0]) for b in bad if b[0] in checks):
        bad.append((checks[idx], '?'))
    return bad, other, len(checks)


if __name__ == '__main__':
    import glob
    os.chdir(ROOT)
    total = 0
    nbad = 0
    for hdr in sys.argv[1:] or sorted(glob.glob('include/game/*.h')):
        res = run(hdr)
        if not res:
            continue
        bad, other, cnt = res
        total += cnt
        nbad += len(bad) + len(other)
        for (t, path, off, rel), ev in sorted(bad, key=lambda b: b[0][2]):
            print(f'{hdr}: {t}.{path} comment 0x{off:X} actual {ev}')
        for o in other[:3]:
            print(f'{hdr}: COMPILE {o}')
    print(f'{total} checks, {nbad} mismatches', file=sys.stderr)
    sys.exit(1 if nbad else 0)
