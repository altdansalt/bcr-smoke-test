#!/usr/bin/env bash
# Lists the pkg_tar output and asserts the expected paths and modes are there.
set -euo pipefail
tarball="$1"
listing="$(tar tvf "$tarball")"
echo "$listing"
grep -q ' opt/smoke/usr/bin/hello$' <<<"$listing"
grep -q ' opt/smoke/usr/share/doc/smoke/NOTICE.txt$' <<<"$listing"
grep -q '^-rwxr-xr-x .* opt/smoke/usr/bin/hello.sh$' <<<"$listing"
grep -q '^lrwxrwxrwx .* opt/smoke/usr/bin/hi -> hello$' <<<"$listing"
echo "tar contents OK"
