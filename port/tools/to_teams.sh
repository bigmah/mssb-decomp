#!/bin/bash
# Exhibition up to the end of team building (1P vs CPU): captains Mario and
# Luigi, both teams filled with "Random". Usage: port/tools/to_teams.sh [secs] [shot-every]
# MSSB_INPUT_EXTRA appends presses after frame ~8000.
E="3200:A,4400:A,5000:A,6200:A,6800:A,7600:UP,7700:UP,7800:UP,7900:A,8600:A,9400:A"
MSSB_INPUT_EXTRA="$E${MSSB_INPUT_EXTRA:+,$MSSB_INPUT_EXTRA}" "$(dirname "$0")/to_menu.sh" "${1:-180}" "${2:-0}"
