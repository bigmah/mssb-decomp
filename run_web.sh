#!/bin/bash
# Build the web version (incremental) and play it in Chrome.
#   ./run_web.sh            build, serve on :8080, open Chrome with the disc loaded
#   ./run_web.sh --no-build skip the build
#   PORT=8081 ./run_web.sh  another port
# Extra page options go in QUERY, e.g. QUERY=movies ./run_web.sh (intro movies).
# Ctrl-C stops the server.
set -e
ROOT="$(cd "$(dirname "$0")" && pwd)"
PORT="${PORT:-8080}"

if [ "$1" != "--no-build" ]; then
  "$ROOT/port/tools/build_web.sh"
fi

URL="http://localhost:$PORT/?iso=disc.iso&autostart${QUERY:+&$QUERY}"
node "$ROOT/port/tools/web_serve.mjs" "$PORT" &
SERVER=$!
trap 'kill $SERVER 2>/dev/null' EXIT INT TERM
sleep 1
echo "Playing at $URL (Ctrl-C to stop)"
open -a "Google Chrome" "$URL" 2>/dev/null || open "$URL"
wait $SERVER
