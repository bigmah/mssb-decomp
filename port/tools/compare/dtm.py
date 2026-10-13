#!/usr/bin/env python3
"""Writes a Dolphin TAS movie (.dtm) from an MSSB_INPUT script.

MSSB_INPUT is the port's scripted-input format (port/src/input.cpp):
"frame:BUTTON,start-end/step:BUTTON,...", each press held for 6 frames
starting at the given PADRead count. Buttons: A B X Y START Z L R UP DOWN
LEFT RIGHT and SLEFT/SRIGHT/SUP/SDOWN (main stick).

The port counts PADRead calls; Dolphin plays one 8-byte controller record per
SI poll. MSSB polls the pads twice per video field (SISetSamplingRate(0)), and
the first frame Dolphin dumps comes LEAD fields after the first poll (both
measured with movies of known length and Dolphin's PauseMovie). Presses are
placed by Dolphin dump frame: `shift(frame)` maps a script frame to the dump
frame it should land on (the port and Dolphin drift apart at loads: see the
scenario offsets in dolphin_compare.py).

  python3 port/tools/compare/dtm.py "500:A,800:START" out.dtm --frames 3000 --offset 84
"""
import argparse
import struct

HOLD = 6  # frames a scripted press is held (port/src/input.cpp)
POLLS_PER_FIELD = 2
LEAD = 13  # dump frame d is polled around poll index POLLS_PER_FIELD * (d + LEAD)

# ControllerState bit positions (Dolphin Core/Movie.h, little-endian bitfield).
BITS = {
    "START": 0, "A": 1, "B": 2, "X": 3, "Y": 4, "Z": 5,
    "UP": 6, "DOWN": 7, "LEFT": 8, "RIGHT": 9, "L": 10, "R": 11,
}
CONNECTED = 1 << 14
STICK = {"SLEFT": (-100, 0), "SRIGHT": (100, 0), "SUP": (0, 100), "SDOWN": (0, -100)}


def parse_script(text):
    """[(frame, name)] for every press in an MSSB_INPUT string."""
    out = []
    for tok in filter(None, (t.strip() for t in text.split(","))):
        if ":" not in tok:
            continue
        when, name = tok.split(":", 1)
        name = name.upper()
        start = end = int(when.split("-")[0])
        step = 1
        if "-" in when:
            rest = when.split("-", 1)[1]
            end = int(rest.split("/")[0])
            if "/" in rest:
                step = int(rest.split("/")[1])
        f = start
        while f <= end and step:
            out.append((f, name))
            f += step
    return out


def write_dtm(path, script, ndump, shift=lambda f: f, game_id=b"GYQE01"):
    """Movie covering dump frames 0..ndump; returns the number of polls."""
    states = [[0, 0, 0] for _ in range(ndump + 1)]
    for frame, name in parse_script(script):
        d = shift(frame)
        for f in range(max(d, 0), min(d + HOLD, ndump + 1)):
            s = states[f]
            if name in BITS:
                s[0] |= 1 << BITS[name]
            elif name in STICK:
                sx, sy = STICK[name]
                s[1] = sx or s[1]
                s[2] = sy or s[2]
    npolls = POLLS_PER_FIELD * (ndump + LEAD)
    body = bytearray()
    for i in range(npolls):
        f = i // POLLS_PER_FIELD - LEAD
        b, sx, sy = states[f] if 0 <= f <= ndump else (0, 0, 0)
        body += struct.pack("<HBBBBBB", b | CONNECTED, 0, 0, (128 + sx) & 0xFF, (128 + sy) & 0xFF, 128, 128)
    hdr = bytearray(256)
    hdr[0:4] = b"DTM\x1a"
    hdr[4:10] = game_id
    hdr[10] = 0  # bWii
    hdr[11] = 1  # controllers: GC port 1
    hdr[12] = 0  # bFromSaveState
    struct.pack_into("<QQQQ", hdr, 13, ndump + LEAD, npolls, 0, 0)  # VI count, input count, lag, unique id
    hdr[49:49 + 7] = b"compare"
    hdr[137] = 0  # bSaveConfig: use the user dir's config
    hdr[151] = 1  # memcards: slot A
    # tickCount: playback ends once the emulated CPU tick count passes it
    # (Movie.cpp CheckInputEnd), so 0 would end the movie at the first poll.
    struct.pack_into("<Q", hdr, 237, 1 << 62)
    with open(path, "wb") as fp:
        fp.write(hdr + body)
    return npolls


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("script")
    ap.add_argument("out")
    ap.add_argument("--frames", type=int, required=True, help="movie length in Dolphin dump frames")
    ap.add_argument("--offset", type=int, default=0, help="dump frame = script frame + offset")
    a = ap.parse_args()
    n = write_dtm(a.out, a.script, a.frames, lambda f: f + a.offset)
    print(f"{a.out}: {n} polls")


if __name__ == "__main__":
    main()
