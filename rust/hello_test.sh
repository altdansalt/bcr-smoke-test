#!/usr/bin/env bash
set -euo pipefail
out="$("$1" Bazel)"
[[ "$out" == '{"name":"Bazel","message":"Hello, Bazel!"}' ]] || { echo "unexpected output: $out"; exit 1; }
