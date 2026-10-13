#!/bin/bash
# Exhibition through the menus into a game (1P Mario vs CPU Luigi, random
# teams, first ball park, default options); the first pitch is at ~t=240s.
# Usage: port/tools/to_game.sh [secs] [shot-every]
MSSB_INPUT_EXTRA="10200:A,11000:A,11800:A,12600:A,13400:A,14200:A${MSSB_INPUT_EXTRA:+,$MSSB_INPUT_EXTRA}" \
  "$(dirname "$0")/to_teams.sh" "${1:-280}" "${2:-0}"
