"""Starlark unit tests (unittest) and analysis tests (analysistest) for greeting.bzl.

Pattern copied and slimmed from bazel-skylib's own tests
(https://github.com/bazelbuild/bazel-skylib/blob/main/tests/unittest_tests.bzl, Apache-2.0).
"""

load("@bazel_skylib//lib:paths.bzl", "paths")
load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts", "unittest")
load(":greeting.bzl", "GreetingInfo", "greeting_line", "greeting_out_name")

# --- unittest: pure Starlark functions ---

def _greeting_line_test_impl(ctx):
    env = unittest.begin(ctx)
    asserts.equals(env, "Hello, BCR!", greeting_line("BCR"))
    asserts.equals(env, "Hi, BCR?", greeting_line("BCR", {"greeting": "Hi", "punctuation": "?"}))
    asserts.equals(env, "hello.txt", greeting_out_name("hello"))
    asserts.equals(env, "hello.txt", greeting_out_name("hello.bin"))
    asserts.equals(env, "a/b/c", paths.join("a", "b", "c"))
    asserts.true(env, paths.is_absolute("/x"), "expected /x to be absolute")
    return unittest.end(env)

greeting_line_test = unittest.make(_greeting_line_test_impl)

# --- analysistest: inspect the providers/actions of a greeting_file target ---

def _greeting_file_analysis_test_impl(ctx):
    env = analysistest.begin(ctx)
    target = analysistest.target_under_test(env)
    asserts.equals(env, "Hello, BCR!", target[GreetingInfo].line)
    files = target[DefaultInfo].files.to_list()
    asserts.equals(env, 1, len(files))
    asserts.equals(env, "greeting_bcr.txt", files[0].basename)
    actions = analysistest.target_actions(env)
    asserts.equals(env, 1, len(actions))
    asserts.equals(env, "FileWrite", actions[0].mnemonic)
    return analysistest.end(env)

greeting_file_analysis_test = analysistest.make(_greeting_file_analysis_test_impl)

def greeting_test_suite(name):
    """Instantiates the unit-test suite and the analysis test.

    Args:
      name: name of the `test_suite`.
    """
    unittest.suite(name, greeting_line_test)
    greeting_file_analysis_test(
        name = name + "_analysis",
        target_under_test = ":greeting_bcr",
    )
