#!/bin/bash
# A scripted exhibition straight from boot (skipfe): Mario vs Bowser at Mario
# Stadium, N innings (default 3), A pressed every 1.5 s (swing / pitch /
# confirm), until the results screen. Usage: port/tools/full_game.sh [innings] [secs] [shot-every]
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
INI="$ROOT/build/port/full_game.ini"
printf 'skipfe = true\ncaptain1 = mario\ncaptain2 = bowser\nstadium = mario\ninnings = %s\n' "${1:-3}" > "$INI"
MSSB_USER_INI="$INI" MSSB_SKIP_MOVIES=1 MSSB_TRACE_GAME=1 MSSB_INPUT="${MSSB_INPUT:-1000-400000/90:A}" \
  "$ROOT/port/tools/run.sh" "${2:-1500}" "${3:-0}"
