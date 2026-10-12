#!/bin/bash
# Boot to the main menu and stay there (no save file: "Create a save file?"
# -> No, "Start the game anyway?" -> Yes). Usage: port/tools/to_menu.sh [secs] [shot-every]
# MSSB_INPUT_EXTRA appends presses (frames, 60/s; the menu is up by ~3000).
IN="500:A,800:A,1300:START,2300:RIGHT,2360:A,2600:LEFT,2660:A"
MSSB_SKIP_MOVIES=1 MSSB_INPUT="$IN${MSSB_INPUT_EXTRA:+,$MSSB_INPUT_EXTRA}" "$(dirname "$0")/run.sh" "${1:-65}" "${2:-0}"
