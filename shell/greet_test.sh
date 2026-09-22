#!/bin/bash
# sh_test: runs the sh_binary (via $(rootpath)) and the C++ binary //cc:hello
# (via rlocation on its $(rlocationpath)) and checks their output.
# --- begin runfiles.bash initialization v3 ---
# Copyright 2020 The Bazel Authors. All rights reserved. Apache-2.0.
# From https://github.com/bazelbuild/bazel/blob/master/tools/bash/runfiles/runfiles.bash
set -uo pipefail; set +e; f=bazel_tools/tools/bash/runfiles/runfiles.bash
# shellcheck disable=SC1090
source "${RUNFILES_DIR:-/dev/null}/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "${RUNFILES_MANIFEST_FILE:-/dev/null}" | cut -f2- -d' ')" 2>/dev/null || \
  source "$0.runfiles/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.exe.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  { echo>&2 "ERROR: cannot find $f"; exit 1; }; f=; set -e
# --- end runfiles.bash initialization v3 ---

greet_bin="$1"           # $(rootpath :greet): relative to the runfiles root (= test cwd)
hello_rloc="$2"          # $(rlocationpath //cc:hello): resolve with rlocation
hello_bin="$(rlocation "$hello_rloc")"

fail() { echo "FAIL: $*" >&2; exit 1; }

[[ -x "$greet_bin" ]] || fail "sh_binary not found at rootpath $greet_bin"
[[ -x "$hello_bin" ]] || fail "cc binary not found via rlocation($hello_rloc) -> $hello_bin"

out="$("$greet_bin" BCR)"
[[ "$out" == "Hello, BCR!" ]] || fail "sh_binary printed: $out"

out="$("$hello_bin")"
[[ "$out" == "Hello, BCR!"* ]] || fail "//cc:hello printed: $out"

echo "PASS"
