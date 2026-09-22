#!/bin/bash
# Merge a package-family workspace (~/work/<name>) into this repo:
# apply its diff vs the common base (everything except MODULE.bazel{,.lock}),
# then append its delimited MODULE.bazel block.
set -euo pipefail
name=$1; base=${2:-16ede91}
repo=$(cd "$(dirname "$0")/.." && pwd); work=$HOME/work/$name
cd "$repo"
git -C "$work" diff --binary "$base" HEAD -- . ':!MODULE.bazel' ':!MODULE.bazel.lock' ':!STATUS.md' ':!NOTES.md' > "/tmp/claude-1000/-home-exedev/d16d82e6-b1cd-4eab-852a-ac99bc00e427/scratchpad/$name.patch"
git apply --3way "/tmp/claude-1000/-home-exedev/d16d82e6-b1cd-4eab-852a-ac99bc00e427/scratchpad/$name.patch"
if grep -q "^# --- $name ---" "$work/MODULE.bazel"; then
  printf '\n' >> MODULE.bazel
  sed -n "/^# --- $name ---/,/^# --- end $name ---/p" "$work/MODULE.bazel" >> MODULE.bazel
else
  echo "WARNING: no '# --- $name ---' block in $work/MODULE.bazel" >&2
fi
echo "merged $name"
