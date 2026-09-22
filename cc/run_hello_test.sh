#!/usr/bin/env bash
set -eu
out="$("$1")"
echo "$out"
case "$out" in "Hello, BCR!"*) ;; *) echo "unexpected output" >&2; exit 1 ;; esac
