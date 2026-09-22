#!/usr/bin/env bash
# Runs the multitool-provided jq from runfiles and checks its version string.
set -euo pipefail
out="$("$1" --version)"
[ "$out" = "jq-1.8.1" ] || { echo "unexpected: $out" >&2; exit 1; }
