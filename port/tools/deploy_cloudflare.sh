#!/bin/bash
# Deploys the web build to Cloudflare (port/cloudflare/).
#   port/tools/deploy_cloudflare.sh          deploy
#   port/tools/deploy_cloudflare.sh dev      run it locally (wrangler dev, http://localhost:8787)
#   port/tools/deploy_cloudflare.sh turn     create a TURN key for online play and store it
#                                            as the Worker's TURN_KEY_ID / TURN_KEY_API_TOKEN secrets (once)
# Needs CLOUDFLARE_API_TOKEN and CLOUDFLARE_ACCOUNT_ID (Workers Scripts edit,
# plus Realtime/Calls admin for `turn`).
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
for f in index.html loader.js net.js pad.js touch.js mssb.js mssb.wasm initial_pipeline_cache.bin.gz; do
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
  # The bytes boot reads up to the main menu, in one file the page streams
  # right away (port/web/boot_ranges.json, from port/tools/record_boot_pack.mjs).
  python3 - "$ISO" "$ROOT/port/web/boot_ranges.json" "$STAGE/disc" "$ID" <<'PY'
import hashlib, json, os, sys
iso, ranges, disc, dir_ = sys.argv[1:]
r = json.load(open(ranges))
if r["size"] != os.path.getsize(iso):
    sys.exit("warning: boot_ranges.json is for another disc image; no boot pack (rerun record_boot_pack.mjs)")
data = bytearray()
with open(iso, "rb") as f:
    for off, n in r["segments"]:
        f.seek(off)
        data += f.read(n)
name = "boot-%s.pack" % hashlib.sha256(data).hexdigest()[:12]
open(os.path.join(disc, dir_, name), "wb").write(data)
m = json.load(open(os.path.join(disc, "manifest.json")))
m["boot"] = {"file": name, "segments": r["segments"]}
json.dump(m, open(os.path.join(disc, "manifest.json"), "w"))
print("Boot pack: %s, %d segments, %.1f MB" % (name, len(r["segments"]), len(data) / 2**20))
PY
else
  echo "warning: no mario_baseball.iso; the site will ask for a disc file" >&2
fi

cd "$ROOT/port/cloudflare"
case "${1:-deploy}" in
  dev) exec $WRANGLER dev --port 8787 ;;
  deploy) $WRANGLER deploy ;;
  turn)
    : "${CLOUDFLARE_API_TOKEN:?}" "${CLOUDFLARE_ACCOUNT_ID:?}"
    KEY=$(curl -sf -X POST -H "Authorization: Bearer $CLOUDFLARE_API_TOKEN" -H 'Content-Type: application/json' \
      -d '{"name":"mssb"}' "https://api.cloudflare.com/client/v4/accounts/$CLOUDFLARE_ACCOUNT_ID/calls/turn_keys")
    node -e 'const r=JSON.parse(process.argv[1]).result; process.stdout.write(r.uid)' "$KEY" | $WRANGLER secret put TURN_KEY_ID
    node -e 'const r=JSON.parse(process.argv[1]).result; process.stdout.write(r.secret)' "$KEY" | $WRANGLER secret put TURN_KEY_API_TOKEN
    echo "TURN key stored as Worker secrets." ;;
  *) echo "usage: $0 [deploy|dev|turn]" >&2; exit 1 ;;
esac
