#!/bin/bash
# Run the PC build for N seconds (default 20), capture its output, always
# clean up. Optionally screenshot the window every few seconds.
#   port/tools/run.sh [seconds] [shot-interval]     (MSSB_ISO picks the disc)
# Log: build/port/run.log. Shots: build/port/shots/tNN.png.
# The crash handler prints a backtrace into the log; MSSB_WATCHDOG_SECS
# arms the hang watchdog. MSSB_RUN_TAG=name runs a copy of the binary with
# its own log/shots (build/port/run-name.log, shots-name/), so several runs
# can go at once.
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
SECS="${1:-20}"; SHOT="${2:-0}"
BIN="$ROOT/build/port/mssb"
LOG="$ROOT/build/port/run.log"
SHOTS="$ROOT/build/port/shots"
WINID="$ROOT/build/port/winid"
if [ -n "$MSSB_RUN_TAG" ]; then
  cp -f "$BIN" "$BIN-$MSSB_RUN_TAG" || exit 1
  BIN="$BIN-$MSSB_RUN_TAG"
  LOG="$ROOT/build/port/run-$MSSB_RUN_TAG.log"
  SHOTS="$ROOT/build/port/shots-$MSSB_RUN_TAG"
fi

pkill -9 -f "$BIN( |\$)" 2>/dev/null
if [ "$SHOT" != 0 ]; then
  [ "$WINID" -nt "$ROOT/port/tools/winid.swift" ] || swiftc -O -o "$WINID" "$ROOT/port/tools/winid.swift" || exit 1
  rm -rf "$SHOTS"; mkdir -p "$SHOTS"
fi

"$BIN" > "$LOG" 2>&1 &
pid=$!
for i in $(seq 1 "$SECS"); do
  sleep 1
  kill -0 $pid 2>/dev/null || break
  if [ "$SHOT" != 0 ] && [ $((i % SHOT)) = 0 ]; then
    id=$("$WINID" $pid) && screencapture -x -o -l"$id" "$SHOTS/t$(printf %02d $i).png"
  fi
done
if kill -0 $pid 2>/dev/null; then
  kill -TERM $pid 2>/dev/null
  for i in 1 2 3; do sleep 1; kill -0 $pid 2>/dev/null || break; done
  kill -9 $pid 2>/dev/null
fi
wait $pid 2>/dev/null
echo "exit=$?" >> "$LOG"
echo "$LOG"
