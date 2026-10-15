#!/usr/bin/env python3
"""Converts GX pipeline lists from config version 13 to 14 (aurora's DynamicAlphaRef: a blended
draw whose alpha test is none or "alpha >= / > n" shares one pipeline, the threshold per draw),
so recorded lists stay usable without playing the games again:

    python3 port/tools/pipeline_convert.py build/pipes2/*.bin build/pipes3/*.bin --out build/pipes-v14
"""
import argparse
import struct
from pathlib import Path

import pipeline_seed as ps

GX, ALPHA, BLEND_MODE = 1, 2640, 2736  # PipelineConfig offsets: shaderConfig.alphaCompare, blendMode
GX_GREATER, GX_GEQUAL, GX_ALWAYS, GX_AOP_AND, GX_BM_BLEND = 4, 6, 7, 0, 1


def convert(kind, version, config):
    if kind != GX or version != 13:
        return version, config
    c = bytearray(config)
    struct.pack_into("<I", c, 0, 14)
    comp0, _ref0, op, comp1, _ref1 = struct.unpack_from("<5I", c, ALPHA)
    blend = struct.unpack_from("<I", c, BLEND_MODE)[0]
    if blend == GX_BM_BLEND and comp1 == GX_ALWAYS and op == GX_AOP_AND and comp0 in (GX_ALWAYS, GX_GEQUAL, GX_GREATER):
        struct.pack_into("<5I", c, ALPHA, GX_GEQUAL, 0x100, GX_AOP_AND, GX_ALWAYS, 0)
    return 14, bytes(c)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("inputs", nargs="+")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    for path in args.inputs:
        seen, blob = set(), bytearray(struct.pack("<II", ps.MAGIC, ps.SCHEMA))
        for kind, version, config, first in ps.read(path):
            version, config = convert(kind, version, config)
            if (kind, config) in seen:
                continue
            seen.add((kind, config))
            blob += ps.REC.pack(kind, version, len(config), first) + config
        name = Path(path).name.replace(".gz", "")
        (out / name).write_bytes(bytes(blob))
        print(f"{path}: {len(ps.read(path))} -> {len(seen)}")


if __name__ == "__main__":
    main()
