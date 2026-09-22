#!/usr/bin/env bash
# Tiny run_binary tool: upper-cases $1 into $2 using only bash builtins.
set -euo pipefail
while IFS= read -r line; do
  printf '%s\n' "${line^^}"
done <"$1" >"$2"
