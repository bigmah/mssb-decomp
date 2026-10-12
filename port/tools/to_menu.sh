#!/bin/bash
# Boot to the main menu (no save file: card prompts answered "No", "start
# anyway") and run for N seconds. Usage: port/tools/to_menu.sh [secs] [shot-every]
IN="500:A,800:A,1300:START"; f=2200
for i in 1 2 3 4 5 6; do IN="$IN,$f:RIGHT,$((f+60)):A,$((f+120)):LEFT,$((f+180)):A"; f=$((f+240)); done
MSSB_SKIP_MOVIES=1 MSSB_INPUT="$IN${MSSB_INPUT_EXTRA:+,$MSSB_INPUT_EXTRA}" "$(dirname "$0")/run.sh" "${1:-75}" "${2:-0}"
