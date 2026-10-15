#!/bin/bash
# Records the web disc's coverage sessions (port/tools/record_disc_reads.mjs,
# four headless Chromes at once, ~22 minutes) and rebuilds the keep-list
# port/web/web_disc.json (port/tools/web_disc.py). Rerun when the disc image,
# the web build's scope or what the game loads changes.
#   - fe: through the front-end menus (with the intro) into an exhibition
#     (1P Mario vs CPU Luigi, random teams), A pressed until it ends
#   - gA, gB, gC: skipfe games, 3 innings, A pressed throughout, whose teams
#     cover all 54 characters and six of the captains
# Needs build/web (port/tools/build_web.sh) and `node port/tools/web_serve.mjs [port]`.
#   port/tools/record_web_disc.sh [port]
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
export NODE_PATH="$ROOT/port/tools/node_modules"
PORT="${1:-8080}"
OUT="$ROOT/build/disc-reads"
rm -rf "$OUT"
mkdir -p "$OUT"
R="node port/tools/record_disc_reads.mjs --port $PORT --secs 1300"
A="MSSB_INPUT=300-600000/90:A"
FE="500:A,800:A,1300:START,3200:A,4400:A,5000:A,6200:A,6800:A,7600:UP,7700:UP,7800:UP,7900:A,8600:A,9400:A"
FE="$FE,10200:A,11000:A,11800:A,12600:A,13400:A,14200:A,15000-400000/90:A"
$R --name fe --query intro --env "MSSB_INPUT=$FE;MSSB_TRACE_GAME=1" > "$OUT/fe.log" 2>&1 &
$R --name gA --query 'skipfe&captain1=mario&captain2=luigi&team1=peach,daisy,yoshi,babymario,babyluigi,bowser,wario,waluigi&team2=koopa,toad,boo,toadette,shyguy,birdo,monty,bowserjr' \
  --env "$A;MSSB_TRACE_GAME=1" > "$OUT/gA.log" 2>&1 &
$R --name gB --query 'skipfe&captain1=dk&captain2=diddy&team1=paratroopa,piantablue,piantared,piantayellow,nokiblue,nokired,nokigreen,hammerbro&team2=toadsworth,toadblue,toadyellow,toadgreen,toadpurple,magikoopablue,magikoopared,magikoopagreen' \
  --env "$A;MSSB_TRACE_GAME=1" > "$OUT/gB.log" 2>&1 &
$R --name gC --query 'skipfe&captain1=yoshi&captain2=birdo&team1=magikoopayellow,kingboo,petey,dixie,goomba,paragoomba,koopared,paratroopagreen&team2=shyguyblue,shyguyyellow,shyguygreen,shyguyblack,drybonesgray,drybonesgreen,drybonesred,drybonesblue' \
  --env "$A;MSSB_TRACE_GAME=1" > "$OUT/gC.log" 2>&1 &
wait
for f in "$OUT"/*.log; do tail -1 "$f"; done
python3 port/tools/web_disc.py --report
