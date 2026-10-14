#!/bin/bash
# Deploys the web build to Cloudflare (port/cloudflare/).
#   port/tools/deploy_cloudflare.sh          deploy
#   port/tools/deploy_cloudflare.sh dev      run it locally (wrangler dev, http://localhost:8787)
# Needs CLOUDFLARE_API_TOKEN and CLOUDFLARE_ACCOUNT_ID (Workers Scripts edit).
# Build first with port/tools/build_web.sh.
# Disc: mario_baseball.iso (repo root, or next to the repo, or $MSSB_ISO) is
# deployed too, as 512 KB chunks (the loader's block size: boot
# touches ~30 scattered blocks, so bigger chunks mostly download unused data) under /disc/<hash>/ that the Worker only serves
# after the page unlocks them with the password (DISC_PASSWORD in
# port/cloudflare/src/worker.js).
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
STAGE="$ROOT/build/cf-assets"
WRANGLER="npx --yes wrangler@4"

rm -rf "$STAGE"
mkdir -p "$STAGE"
for f in index.html loader.js pad.js touch.js mssb.js mssb.wasm initial_pipeline_cache.bin.gz; do
  cp "$ROOT/build/web/$f" "$STAGE/"
done

ISO="${MSSB_ISO:-}"
for p in "$ROOT/mario_baseball.iso" "$ROOT/../mario_baseball.iso"; do
  [ -z "$ISO" ] && [ -f "$p" ] && ISO="$p"
done
if [ -n "$ISO" ] && [ -f "$ISO" ]; then
  ID=$(shasum -a 256 "$ISO" | cut -c1-12)
  mkdir -p "$STAGE/disc/$ID"
  split -b 512k -a 3 "$ISO" "$STAGE/disc/$ID/"
  COUNT=$(ls "$STAGE/disc/$ID" | wc -l | tr -d ' ')
  echo "{\"size\":$(stat -f %z "$ISO"),\"chunk\":524288,\"count\":$COUNT,\"dir\":\"$ID\"}" > "$STAGE/disc/manifest.json"
  echo "Disc: $COUNT chunks in disc/$ID ($ISO)"
else
  echo "warning: no mario_baseball.iso; the site will ask for a disc file" >&2
fi

cd "$ROOT/port/cloudflare"
case "${1:-deploy}" in
  dev) exec $WRANGLER dev --port 8787 ;;
  deploy) $WRANGLER deploy ;;
  *) echo "usage: $0 [deploy|dev]" >&2; exit 1 ;;
esac
