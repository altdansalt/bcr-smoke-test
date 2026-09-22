#!/usr/bin/env bash
# Lists the pkg_tar output with the hermetic bsdtar (tar.bzl toolchain) and asserts
# the expected paths, modes and symlink are there.
set -euo pipefail
tar_bin="$1"   # $(BSDTAR_BIN): an execroot path like external/<repo>/tar
tarball="$2"
# Tests run inside the runfiles tree, where external repos live next to _main.
if [[ ! -x "$tar_bin" && "$tar_bin" == external/* ]]; then
  tar_bin="${RUNFILES_DIR:-$TEST_SRCDIR}/${tar_bin#external/}"
fi
listing="$("$tar_bin" tvf "$tarball")"
echo "$listing"
grep -q ' opt/smoke/usr/bin/hello$' <<<"$listing"
grep -q ' opt/smoke/usr/share/doc/smoke/NOTICE.txt$' <<<"$listing"
grep -q '^-rwxr-xr-x .* opt/smoke/usr/bin/hello.sh$' <<<"$listing"
grep -q '^l[rwx-]* .* opt/smoke/usr/bin/hi -> hello$' <<<"$listing"
echo "tar contents OK"
