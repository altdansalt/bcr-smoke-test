"""Tests for features.bzl: unittest on the feature value types, analysistest on the gated action."""

load("@bazel_features//:features.bzl", "bazel_features")
load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts", "unittest")
load(":features.bzl", "WRITE_MNEMONIC")

def _feature_types_test_impl(ctx):
    env = unittest.begin(ctx)
    asserts.equals(env, "bool", type(bazel_features.rules.write_action_has_mnemonic))
    asserts.equals(env, "bool", type(bazel_features.external_deps.bazel_mod_tidy))
    asserts.equals(env, "string", type(bazel_features.flags.allow_unresolved_symlinks))
    asserts.true(env, bazel_features.external_deps.is_bzlmod_enabled, "expected bzlmod to be enabled")
    asserts.true(env, bazel_features.globals.DefaultInfo == DefaultInfo, "globals.DefaultInfo mismatch")
    return unittest.end(env)

feature_types_test = unittest.make(_feature_types_test_impl)

def _features_file_analysis_test_impl(ctx):
    env = analysistest.begin(ctx)
    actions = analysistest.target_actions(env)
    asserts.equals(env, 1, len(actions))
    asserts.equals(env, WRITE_MNEMONIC, actions[0].mnemonic)
    return analysistest.end(env)

features_file_analysis_test = analysistest.make(_features_file_analysis_test_impl)

def features_test_suite(name):
    """Instantiates the unit-test suite and the analysis test.

    Args:
      name: name of the `test_suite`.
    """
    unittest.suite(name, feature_types_test)
    features_file_analysis_test(name = name + "_analysis", target_under_test = ":features")
