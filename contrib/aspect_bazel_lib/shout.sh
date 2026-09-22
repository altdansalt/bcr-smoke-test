#!/usr/bin/env bash
# Tiny run_binary tool: upper-cases $1 into $2 (POSIX sh + tr only; no bash-4 features
# so it also works with macOS's bash 3.2).
set -eu
tr '[:lower:]' '[:upper:]' <"$1" >"$2"
