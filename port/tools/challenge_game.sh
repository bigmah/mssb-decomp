#!/bin/bash
# Challenge mode: boot to the main menu (to_menu.sh), enter Challenge, mash A
# through the setup (new save slot, Mario captain, intro talk) until the map,
# then play MSSB_CHALLENGE_INPUT (frames, 60/s; the map is up by ~6600).
# Usage: port/tools/challenge_game.sh [secs] [shot-every]
# Use MSSB_USER_DIR=<empty dir> for a fresh memory card.
# Log: build/port/run-challenge.log, shots in build/port/shots-challenge/.
IN="3200:DOWN,3300:A,3440-6600/90:A"
MSSB_RUN_TAG=challenge MSSB_INPUT_EXTRA="$IN${MSSB_CHALLENGE_INPUT:+,$MSSB_CHALLENGE_INPUT}" \
  "$(dirname "$0")/to_menu.sh" "${1:-300}" "${2:-0}"
