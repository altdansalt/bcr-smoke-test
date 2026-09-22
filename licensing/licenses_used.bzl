"""`licenses_used`: writes the transitive license info of `deps` as JSON.

Copied and slimmed from rules_license's sample report
https://github.com/bazelbuild/rules_license/blob/main/sample_reports/licenses_used.bzl (Apache-2.0).
"""

load(
    "@rules_license//rules:gather_licenses_info.bzl",
    "gather_licenses_info",
    "write_licenses_info",
)

def _licenses_used_impl(ctx):
    write_licenses_info(ctx, ctx.attr.deps, ctx.outputs.out)
    return [DefaultInfo(files = depset([ctx.outputs.out]))]

licenses_used = rule(
    implementation = _licenses_used_impl,
    doc = "Collects `LicenseInfo` from `deps` (via the `gather_licenses_info` aspect) into a JSON file.",
    attrs = {
        "deps": attr.label_list(
            doc = "Targets to collect license info for.",
            aspects = [gather_licenses_info],
        ),
        "out": attr.output(
            doc = "The JSON output file.",
            mandatory = True,
        ),
    },
)
