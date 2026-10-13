#!/bin/bash
# Smoke test of a main-menu mode: boot to the menu (to_menu.sh), move down to
# the mode, enter it, then press A every 1.5 s (and whatever MSSB_MODE_INPUT
# adds) for N seconds. Usage: port/tools/mode.sh challenge|toyfield|minigames|practice [secs] [shot-every]
# Log: build/port/run-<mode>.log, shots in build/port/shots-<mode>/.
case "$1" in
  exhibition) n=0 ;; challenge) n=1 ;; toyfield) n=2 ;; minigames) n=3 ;; practice) n=4 ;;
  *) echo "usage: $0 challenge|toyfield|minigames|practice [secs] [shot-every]"; exit 1 ;;
esac
IN=""; f=3200
for i in $(seq 1 $n); do IN="$IN$f:DOWN,"; f=$((f+40)); done
IN="${IN}$((f+60)):A,$((f+200))-200000/90:A"
MSSB_RUN_TAG="$1" MSSB_INPUT_EXTRA="$IN${MSSB_MODE_INPUT:+,$MSSB_MODE_INPUT}" \
  "$(dirname "$0")/to_menu.sh" "${2:-150}" "${3:-0}"
