#!/bin/bash
# Checks that the licenses_used JSON report mentions our license target and SPDX kind.
set -euo pipefail
json="$1"
grep -q '"license_kinds"' "$json" || { echo "no license_kinds in $json"; cat "$json"; exit 1; }
grep -q 'Apache-2.0' "$json" || { echo "Apache-2.0 not found in $json"; cat "$json"; exit 1; }
grep -q '//license:license' "$json" || { echo "//license:license not found in $json"; cat "$json"; exit 1; }
echo PASS
