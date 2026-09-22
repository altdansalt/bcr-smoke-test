# license — rules_license 1.0.0 + package_metadata 0.0.13

Exercises: `license()` with `license_kinds = ["@rules_license//licenses/spdx:Apache-2.0"]`,
`package_info()`, the Bazel 9 `package(default_package_metadata = [...])` attribute,
`@package_metadata//rules:package_metadata.bzl` (`package_metadata`) and
`@package_metadata//licenses/rules:license.bzl` (`license` with an SPDX `license_kind`),
a `build_test` over all of them, and a `licenses_used` report rule built on the
`gather_licenses_info` aspect + `write_licenses_info()` (checked by an `sh_test`).

Gotcha: rules_license 1.0.0's `write_licenses_info()` fails at analysis time
(`TransitiveLicensesInfo has no field target_under_license`) if any dep carries no license
metadata, so the report only lists targets from this package.

Attribution: `licenses_used.bzl` is copied and slimmed from
https://github.com/bazelbuild/rules_license/blob/main/sample_reports/licenses_used.bzl (Apache-2.0).
