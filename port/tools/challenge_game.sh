#!/bin/bash
# Challenge mode, one match: boot to the main menu (to_menu.sh), enter
# Challenge, mash A through the setup (new save, Mario captain, intro talk),
# walk the map (d-pad up, left, left, left) into Bowser Jr., who challenges
# Mario; mash A through that match (bottom of the 9th) and its post-game talk,
# then B (cursor to Exit) and A out of the status screen back onto the map.
# MSSB_CHALLENGE_INPUT replaces the map/match input (frames, 60/s; the map
# is up by ~8500). Usage: port/tools/challenge_game.sh [secs] [shot-every]
# A fresh memory card per run unless MSSB_USER_DIR is set.
# Log: build/port/run-challenge.log, shots in build/port/shots-challenge/.
IN="3200:DOWN,3300:A,3440-8400/90:A"
MAP="8600:UP,8900:LEFT,9200:LEFT,9500:LEFT,9800-24000/90:A,24000-25000/120:B,25300:A"
MSSB_RUN_TAG=challenge MSSB_INPUT_EXTRA="$IN,${MSSB_CHALLENGE_INPUT:-$MAP}" \
  "$(dirname "$0")/to_menu.sh" "${1:-480}" "${2:-0}"
