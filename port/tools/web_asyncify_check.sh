#!/bin/bash
# Links the web build again with Asyncify's run-time checks into build/web-acheck:
# a function left out of Asyncify (port/web/asyncify_remove.json) that is on
# the stack when the game suspends then traps ("unreachable") instead of
# corrupting the game. Run the game in it (MSSB_WEB_DIR=build/web-acheck
# node port/tools/web_serve.mjs 8088) through whatever the list's change touches.
# (-sASSERTIONS would add them too, but trips over SDL's audio EM_ASM.)
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
OUT="$ROOT/build/web-acheck"
BYN="$OUT/binaryen"
REAL="$(em-config BINARYEN_ROOT)"
mkdir -p "$BYN/bin"
for f in "$REAL"/bin/*; do ln -sf "$f" "$BYN/bin/"; done
ln -sfn "$REAL/include" "$BYN/include"
ln -sfn "$REAL/lib" "$BYN/lib"
rm -f "$BYN/bin/wasm-opt"
cat > "$BYN/bin/wasm-opt" <<WRAP
#!/bin/bash
for a in "\$@"; do [ "\$a" = "--asyncify" ] && exec "$REAL/bin/wasm-opt" --pass-arg=asyncify-asserts "\$@"; done
exec "$REAL/bin/wasm-opt" "\$@"
WRAP
chmod +x "$BYN/bin/wasm-opt"
cd "$ROOT/build/web"
CMD=$(ninja -t commands mssb | tail -1 | sed "s# -o mssb.js# -o $OUT/mssb.js#")
EM_BINARYEN_ROOT="$BYN" eval "$CMD"
cp index.html loader.js net.js pad.js touch.js initial_pipeline_cache.bin.gz "$OUT/"
echo "$OUT"
