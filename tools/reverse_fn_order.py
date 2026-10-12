#!/usr/bin/env python3
"""Reorder the functions of a REL source file into reverse address order.

The RELs are built with `-inline deferred`, which makes mwcc emit a file's
functions in reverse source order. To link a unit, its source must therefore
list functions from the highest .text address to the lowest.

A function block is the `// .text:0x...` comment, any comment / `#if
NONMATCHING` lines directly above it, the definition and a closing `#endif`.
Everything else (types, data, static inline helpers, pragmas) keeps its order
and is placed before the reordered functions, so declarations still precede
their uses.

Usage: python3 tools/reverse_fn_order.py src/challenge/rep_7BA0.c [--check]
"""
import re
import sys

TEXT_RE = re.compile(r"^// \.text:0x([0-9A-Fa-f]+)")


def blocks_of(lines):
    blocks = []  # (start, end_exclusive, addr)
    i = 0
    n = len(lines)
    while i < n:
        m = TEXT_RE.match(lines[i])
        if not m:
            i += 1
            continue
        start = i
        while start > 0:
            prev = lines[start - 1].strip()
            if (prev.startswith("//") and not TEXT_RE.match(lines[start - 1])) or prev.startswith("#if NONMATCHING"):
                if blocks and start - 1 < blocks[-1][1]:
                    break
                start -= 1
            else:
                break
        in_if = any(lines[k].strip().startswith("#if NONMATCHING") for k in range(start, i + 1))
        j = i + 1
        depth = 0
        seen = False
        header_inline = None
        while j < n:
            if depth == 0 and not seen and lines[j].strip() and not lines[j].lstrip().startswith(("//", "/*", "*", "#")):
                header_inline = "inline" in lines[j].split("(")[0]
            depth += lines[j].count("{") - lines[j].count("}")
            if "{" in lines[j]:
                seen = True
            j += 1
            if seen and depth == 0:
                if header_inline:
                    # A static inline helper sits between the marker and the
                    # function: keep going to the function itself.
                    seen = False
                    header_inline = None
                    continue
                break
        if in_if:
            while j < n and not lines[j].strip().startswith("#endif"):
                j += 1
            j += 1
        blocks.append((start, j, int(m.group(1), 16)))
        i = j
    return blocks


def main():
    path = sys.argv[1]
    check = "--check" in sys.argv
    lines = open(path).read().split("\n")
    blocks = blocks_of(lines)
    addrs = [b[2] for b in blocks]
    if addrs == sorted(addrs, reverse=True):
        print(f"{path}: already in reverse order")
        return
    if check:
        print(f"{path}: not in reverse order")
        sys.exit(1)
    first = blocks[0][0]
    last = blocks[-1][1]
    inblock = set()
    for s, e, _ in blocks:
        inblock.update(range(s, e))
    head = lines[:first]
    others = [lines[k] for k in range(first, last) if k not in inblock]
    # Drop runs of blank lines left behind.
    cleaned = []
    for l in others:
        if l.strip() == "" and (not cleaned or cleaned[-1].strip() == ""):
            continue
        cleaned.append(l)
    body = []
    for s, e, _ in sorted(blocks, key=lambda b: -b[2]):
        chunk = lines[s:e]
        body.extend(chunk)
        body.append("")
    out = head + cleaned
    if out and out[-1].strip() != "":
        out.append("")
    out += body
    tail = lines[last:]
    while tail and tail[0].strip() == "":
        tail.pop(0)
    out += tail
    if out[-1] != "":
        out.append("")
    open(path, "w").write("\n".join(out).rstrip("\n") + "\n")
    print(f"{path}: reordered {len(blocks)} functions")


if __name__ == "__main__":
    main()
