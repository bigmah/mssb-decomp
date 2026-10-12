#!/bin/bash
# Run the PC build under lldb with the to_menu.sh input; stops at the first
# crash and prints the backtrace, frame variables and any extra lldb commands.
# Usage: port/tools/dbg.sh [secs] ["lldb cmd" ...]   (MSSB_INPUT_EXTRA as to_menu.sh)
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
SECS="${1:-90}"; shift
IN="500:A,800:A,1300:START,2300:RIGHT,2360:A,2600:LEFT,2660:A"
args=(-o "process handle SIGUSR1 SIGUSR2 -s false -p true" -o run -k "bt 8" -k "frame variable")
for c in "$@"; do args+=(-k "$c"); done
MSSB_SKIP_MOVIES=1 MSSB_INPUT="$IN${MSSB_INPUT_EXTRA:+,$MSSB_INPUT_EXTRA}" \
  timeout "$SECS" lldb -b "${args[@]}" -k kill "$ROOT/build/port/mssb" 2>&1
