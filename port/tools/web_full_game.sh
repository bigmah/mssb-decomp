#!/bin/bash
# The web build in headless Chrome: boot through the front-end menus (no
# skipfe) into an exhibition (1P Mario vs CPU Luigi, random teams, default
# options: 3 innings), then A every 1.5 s until the game ends. Same input as
# port/tools/to_game.sh. Needs build/web (port/tools/build_web.sh) and a
# running `node port/tools/web_serve.mjs PORT`.
# Usage: port/tools/web_full_game.sh [port] [secs] [shots] (shots: comma-separated seconds)
# Console log: build/web-game/console.log; shots: build/web-game/shot-NNNN.png.
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
PORT="${1:-8080}"
IN="500:A,800:A,1300:START,2300:RIGHT,2360:A,2600:LEFT,2660:A,3200:A,4400:A,5000:A,6200:A,6800:A"
IN="$IN,7600:UP,7700:UP,7800:UP,7900:A,8600:A,9400:A,10200:A,11000:A,11800:A,12600:A,13400:A,14200:A"
IN="$IN,15000-400000/90:A"
node "$ROOT/port/tools/web_drive.mjs" --secs "${2:-1000}" --shots "${3:-120,300,600,900}" \
  --url "http://localhost:$PORT/?iso=disc.iso&autostart&nomovies&stats&env=MSSB_INPUT=$IN;MSSB_TRACE_GAME=1" \
  --out "$ROOT/build/web-game"
