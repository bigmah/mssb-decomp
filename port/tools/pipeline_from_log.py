#!/usr/bin/env python3
"""Rebuilds the pipeline lists that ?debug pages post to the site's log (port/web/loader.js,
reportPipelines) from a `wrangler tail` capture, one file per page session:

    python3 port/tools/pipeline_from_log.py build/wrangler-tail.log build/pipes-live
    python3 port/tools/pipeline_seed.py build/pipes-live/*.bin   # merge into the seed
"""
import base64
import gzip
import re
import sys
from collections import defaultdict
from pathlib import Path

LINE = re.compile(r"\[(\w+)\] [\d.]+ log \[pipelist\] (\d+) (\d+) (\d+)/(\d+) (\S+)")


def main():
    log, out = Path(sys.argv[1]), Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    parts = defaultdict(lambda: defaultdict(dict))  # session -> part -> (start, i) -> b64
    totals = {}
    for line in log.read_text(errors="replace").splitlines():
        m = LINE.search(line)
        if m:
            session, part, start, i, n, b64 = m.groups()
            parts[session][(int(part), int(start))][int(i)] = b64
            totals[(session, int(part))] = int(n)
    for session, chunks in parts.items():
        data = bytearray()
        for (part, start), lines in sorted(chunks.items()):
            if len(lines) != totals[(session, part)] or start != len(data):
                print(f"{session}: part {part} incomplete, stopping there")
                break
            data += gzip.decompress(base64.b64decode("".join(lines[i] for i in sorted(lines))))
        if data:
            (out / f"{session}.bin").write_bytes(data)
            print(f"{session}: {len(data)} bytes")


if __name__ == "__main__":
    main()
