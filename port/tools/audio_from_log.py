#!/usr/bin/env python3
"""Turns the audio a ?debug page posted to the site log (the "static!" button, port/web/loader.js
[audiodump] lines) back into WAV files, one per tap:

    python3 port/tools/audio_from_log.py build/wrangler-tail.log build/audiodumps
"""
import base64
import gzip
import re
import sys
import wave
from collections import defaultdict
from pathlib import Path

LINE = re.compile(r"\[(\w+)\] [\d.]+ log \[audiodump\] (\d+) (\d+) (\d+)/(\d+) (\S+)")


def main():
    log, out = Path(sys.argv[1]), Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    parts = defaultdict(dict)
    meta = {}
    for line in log.read_text(errors="replace").splitlines():
        m = LINE.search(line)
        if m:
            session, dump, rate, i, n, b64 = m.groups()
            parts[(session, dump)][int(i)] = b64
            meta[(session, dump)] = (int(rate), int(n))
    for key, lines in sorted(parts.items()):
        rate, n = meta[key]
        if len(lines) != n:
            print(f"{key[0]} #{key[1]}: {len(lines)} of {n} lines, skipped")
            continue
        pcm = gzip.decompress(base64.b64decode("".join(lines[i] for i in range(1, n + 1))))
        path = out / f"{key[0]}-{key[1]}.wav"
        with wave.open(str(path), "wb") as w:
            w.setnchannels(2)
            w.setsampwidth(2)
            w.setframerate(rate)
            w.writeframes(pcm)
        print(f"{path}: {len(pcm) // 4 / rate:.1f} s")


if __name__ == "__main__":
    main()
