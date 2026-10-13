#!/bin/bash
# Builds the browser version into build/web (Emscripten: brew install emscripten).
#   port/tools/build_web.sh
# Then: node port/tools/web_serve.mjs and open http://localhost:8080 in Chrome.
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
if [ ! -f "$ROOT/build/web/build.ninja" ]; then
  emcmake cmake -S "$ROOT/port" -B "$ROOT/build/web" -G Ninja -DCMAKE_BUILD_TYPE=Release
fi
ninja -C "$ROOT/build/web" mssb mssb_page
