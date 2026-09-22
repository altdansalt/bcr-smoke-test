#!/usr/bin/env bash
set -euo pipefail
out="$("$1" Perl)"
echo "$out"
[[ "$out" == "Hello, Perl!" ]]
