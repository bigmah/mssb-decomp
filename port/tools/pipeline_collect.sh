#!/bin/bash
# Plays scripted scenarios in the web build (headless Chrome, a few at a time)
# and merges the GPU pipelines they use into port/web/initial_pipeline_cache.bin.gz
# (port/tools/pipeline_seed.py). Rerun after aurora changes its pipeline config
# version (the page then ignores the old seed). Needs build/web and a running
# `node port/tools/web_serve.mjs PORT`.
# Usage: port/tools/pipeline_collect.sh [port] [secs] [parallel] [scenario...]
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
PORT="${1:-8080}"
SECS="${2:-300}"
PAR="${3:-4}"
shift $(($# < 3 ? $# : 3))
OUT="${PIPES_OUT:-$ROOT/build/pipes}" # PIPES_OUT: somewhere else
mkdir -p "$OUT"

MENU="500:A,800:A,1300:START"
# Front end into an exhibition (same input as web_full_game.sh).
EXHIB="$MENU,3200:A,4400:A,5000:A,6200:A,6800:A,7600:UP,7700:UP,7800:UP,7900:A,8600:A,9400:A,10200:A,11000:A"
EXHIB="$EXHIB,11800:A,12600:A,13400:A,14200:A,15000-400000/90:A"
mode() { # main-menu mode n (mode.sh): down n times, A, then A every 1.5 s
  local IN="$MENU" f=3200 i
  for ((i = 0; i < $1; i++)); do IN="$IN,$f:DOWN"; f=$((f + 40)); done
  echo "$IN,$((f + 60)):A,$((f + 200))-400000/90:A"
}
GAME="600-400000/90:A"
# Like a person playing: swings, pitches and throws aimed around, fielders run, buttons mixed in
# (no START: the pause menu could end the game). More of the game's effects show up than with A alone.
MIX="600-400000/90:A,640-400000/130:SLEFT,700-400000/170:SRIGHT,760-400000/210:SUP,820-400000/250:SDOWN"
MIX="$MIX,880-400000/290:B,940-400000/370:Y,1000-400000/410:X,1060-400000/450:R,1120-400000/530:Z"

query() {
  case "$1" in
    frontend) echo "movies&env=MSSB_INPUT=$EXHIB" ;;
    mario) echo "skipfe&captain1=mario&captain2=bowser&stadium=mario&env=MSSB_INPUT=$GAME" ;;
    bowser) echo "skipfe&captain1=bowser&captain2=wario&stadium=bowser&env=MSSB_INPUT=$GAME" ;;
    wario) echo "skipfe&captain1=wario&captain2=dk&stadium=wario&env=MSSB_INPUT=$GAME" ;;
    yoshi) echo "skipfe&captain1=yoshi&captain2=birdo&stadium=yoshi&env=MSSB_INPUT=$GAME" ;;
    peach) echo "skipfe&captain1=peach&captain2=daisy&stadium=peach&env=MSSB_INPUT=$GAME" ;;
    dk) echo "skipfe&captain1=dk&captain2=diddy&stadium=dk&env=MSSB_INPUT=$GAME" ;;
    challenge) echo "env=MSSB_ALLMODES=1;MSSB_INPUT=$(mode 1)" ;;
    toyfield) echo "env=MSSB_ALLMODES=1;MSSB_INPUT=$(mode 2)" ;;
    minigames) echo "env=MSSB_ALLMODES=1;MSSB_INPUT=$(mode 3)" ;;
    practice) echo "env=MSSB_INPUT=$(mode 4)" ;;
    mx-*-*) # the same with mixed input: mx-peach-daisy
      local c="${1#mx-}"
      echo "skipfe&captain1=${c%-*}&captain2=${c#*-}&stadium=mario&env=MSSB_INPUT=$MIX" ;;
    ms-*-*) # a game at Mario Stadium (the web build's scope) between two captains: ms-peach-daisy
      local c="${1#ms-}"
      echo "skipfe&captain1=${c%-*}&captain2=${c#*-}&stadium=mario&env=MSSB_INPUT=$GAME" ;;
  esac
}

names=("$@")
[ ${#names[@]} -eq 0 ] && names=(frontend mario practice) # what the PC menus offer (port/game/menu_scope.c); the others by name
run() {
  local name="$1"
  rm -f "$OUT/$name.bin"
  node "$ROOT/port/tools/web_drive.mjs" --quiet 1 --secs "$SECS" --out "$OUT/$name" \
    --url "http://localhost:$PORT/?iso=disc.iso&autostart&noseed&nomovies&$(query "$name")" \
    --fetch "/mssb/pipeline_cache.bin:$OUT/$name.bin" >/dev/null 2>&1
  echo "$name: $( [ -f "$OUT/$name.bin" ] && python3 "$ROOT/port/tools/pipeline_seed.py" --stats "$OUT/$name.bin" | head -1 || echo 'nothing new')"
}
for name in "${names[@]}"; do
  [ -z "$(query "$name")" ] && { echo "unknown scenario $name"; exit 1; }
  run "$name" &
  while [ "$(jobs -r | wc -l)" -ge "$PAR" ]; do sleep 2; done
done
wait
bins=()
for name in "${names[@]}"; do [ -f "$OUT/$name.bin" ] && bins+=("$OUT/$name.bin"); done
[ ${#bins[@]} -gt 0 ] && python3 "$ROOT/port/tools/pipeline_seed.py" "${bins[@]}"
