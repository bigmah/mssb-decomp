#!/usr/bin/env python3
"""Reorder the functions of a REL source file into reverse address order.

The RELs are built with `-inline deferred`, which makes mwcc emit a file's
functions in reverse source order. To link a unit, its source must therefore
list functions from the highest .text address to the lowest.

A function block is a top-level function definition (its address comes from
the module's symbols.txt), the comment lines directly above it, and an
enclosing `#if NONMATCHING` ... `#endif`. Everything else (types, data,
static inline helpers, pragmas) keeps its order and is placed before the
reordered functions, so declarations still precede their uses.

Usage: python3 tools/reverse_fn_order.py src/challenge/rep_7BA0.c [--check]
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEF_RE = re.compile(r"^[A-Za-z_][\w\s\*]*?\b(\w+)\s*\(")


def load_addrs(path):
    rel = os.path.relpath(os.path.abspath(path), os.path.join(ROOT, "src"))
    module = rel.split(os.sep)[0]
    symfile = os.path.join(ROOT, "config", "GYQE01", module, "symbols.txt")
    if not os.path.exists(symfile):
        symfile = os.path.join(ROOT, "config", "GYQE01", "symbols.txt")
    addrs = {}
    for line in open(symfile):
        m = re.match(r"(\S+) = \.text:0x([0-9A-Fa-f]+);", line)
        if m:
            addrs[m.group(1)] = int(m.group(2), 16)
    return addrs


def items_of(lines):
    """Split into top-level items: (start, end, kind, name)."""
    items = []
    i, n = 0, len(lines)
    while i < n:
        line = lines[i]
        s = line.strip()
        if s.startswith("#if NONMATCHING"):
            depth = 0
            j = i
            while j < n:
                t = lines[j].strip()
                if t.startswith("#if"):
                    depth += 1
                elif t.startswith("#endif"):
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            inner = items_of(lines[i + 1:j])
            names = [it[3] for it in inner if it[2] == "fn"]
            if len(names) > 1:
                print(f"warning: one #if NONMATCHING block holds {names}", file=sys.stderr)
            items.append((i, j + 1, "fn" if names else "other", names[0] if names else None))
            i = j + 1
            continue
        m = DEF_RE.match(line)
        if m and not s.startswith(("typedef", "extern", "struct", "union", "enum", "#", "return")):
            # find the end of the header: '{' (definition) or ';' (declaration)
            j = i
            header = ""
            while j < n:
                header += lines[j]
                if "{" in lines[j] or ";" in lines[j]:
                    break
                j += 1
            if j < n and "{" in lines[j] and "=" not in header.split("{")[0]:
                depth = 0
                k = j
                while k < n:
                    depth += lines[k].count("{") - lines[k].count("}")
                    k += 1
                    if depth == 0:
                        break
                inline = "inline" in header.split("(")[0]
                items.append((i, k, "inline" if inline else "fn", m.group(1)))
                i = k
                continue
        items.append((i, i + 1, "other", None))
        i += 1
    return items


def main():
    path = sys.argv[1]
    check = "--check" in sys.argv
    addrs = load_addrs(path)
    lines = open(path).read().split("\n")
    items = items_of(lines)
    blocks = []
    for s, e, kind, name in items:
        if kind != "fn":
            continue
        if name not in addrs:
            sys.exit(f"{path}: no address for {name}")
        # take the comment lines directly above the definition along
        start = s
        while start > 0:
            prev = lines[start - 1].strip()
            if prev.startswith(("//", "/*", "*", "#pragma")):
                start -= 1
            else:
                break
        # a #pragma right after the function (closing a pragma pair) belongs to it
        end = e
        k = e
        while k < len(lines) and lines[k].strip() == "":
            k += 1
        has_pragma_above = any(lines[x].strip().startswith("#pragma") for x in range(start, s))
        while has_pragma_above and k < len(lines) and lines[k].strip().startswith("#pragma"):
            k += 1
            end = k
        blocks.append([start, end, addrs[name], name])
    for a, b in zip(blocks, blocks[1:]):
        if b[0] < a[1]:
            b[0] = a[1]
    addr_list = [b[2] for b in blocks]
    if addr_list == sorted(addr_list, reverse=True):
        print(f"{path}: already in reverse order")
        return
    if check:
        print(f"{path}: not in reverse order")
        sys.exit(1)
    first = blocks[0][0]
    last = blocks[-1][1]
    inblock = set()
    for s, e, _, _ in blocks:
        inblock.update(range(s, e))
    head = lines[:first]
    others = [lines[k] for k in range(first, last) if k not in inblock]
    cleaned = []
    for l in others:
        if l.strip() == "" and (not cleaned or cleaned[-1].strip() == ""):
            continue
        cleaned.append(l)
    body = []
    for s, e, _, _ in sorted(blocks, key=lambda b: -b[2]):
        chunk = lines[s:e]
        while chunk and chunk[-1].strip() == "":
            chunk.pop()
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
    open(path, "w").write("\n".join(out).rstrip("\n") + "\n")
    print(f"{path}: reordered {len(blocks)} functions")


if __name__ == "__main__":
    main()
