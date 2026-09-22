"""bazel_features smoke: a rule that branches on `bazel_features` at analysis time."""

load("@bazel_features//:features.bzl", "bazel_features")

# Rule attributes that only exist on newer Bazels are gated by feature flags like this.
WRITE_MNEMONIC = "FeaturesWrite" if bazel_features.rules.write_action_has_mnemonic else "FileWrite"

def _features_file_impl(ctx):
    out = ctx.actions.declare_file(ctx.label.name + ".txt")
    content = "\n".join([
        "bzlmod=%s" % bazel_features.external_deps.is_bzlmod_enabled,
        "bazel_mod_tidy=%s" % bazel_features.external_deps.bazel_mod_tidy,
        "allow_unresolved_symlinks_flag=%s" % bazel_features.flags.allow_unresolved_symlinks,
        "cc_common_is_in_rules_cc=%s" % bazel_features.cc.cc_common_is_in_rules_cc,
        "has_default_test_toolchain_type=%s" % bazel_features.toolchains.has_default_test_toolchain_type,
    ]) + "\n"
    if bazel_features.rules.write_action_has_mnemonic:
        ctx.actions.write(out, content, mnemonic = WRITE_MNEMONIC)
    else:
        ctx.actions.write(out, content)
    return [DefaultInfo(files = depset([out]))]

features_file = rule(
    implementation = _features_file_impl,
    doc = "Writes a few `bazel_features` values to `<name>.txt`.",
)
