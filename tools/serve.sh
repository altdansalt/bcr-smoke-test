#!/bin/bash
# Serve the progress site on 0.0.0.0:8000 (re-render on each request cycle via a loop).
cd "$(dirname "$0")/.." || exit 1
mkdir -p site
( while true; do python3 tools/mksite.py; sleep 15; done ) &
exec python3 -m http.server 8000 --bind 0.0.0.0 --directory site
