"""py_test (unittest) covering the py_library and the pip deps from requirements_lock.txt."""

import sys
import unittest

import tomli

from python import greeter


class GreeterTest(unittest.TestCase):
    def test_greet(self):
        self.assertEqual(greeter.greet("Bazel"), "Hello, Bazel!")

    def test_greet_all_from_yaml(self):
        self.assertEqual(
            greeter.greet_all("names: [a, b]"),
            ["Hello, a!", "Hello, b!"],
        )

    def test_tomli_pip_dep(self):
        self.assertEqual(tomli.loads('x = 1\n[t]\ny = "z"'), {"x": 1, "t": {"y": "z"}})

    def test_hermetic_toolchain(self):
        # The rules_python toolchain registered in MODULE.bazel, not a system interpreter.
        self.assertEqual(sys.version_info[:2], (3, 12), sys.version)
        self.assertFalse(sys.prefix.startswith("/usr"), sys.prefix)


if __name__ == "__main__":
    unittest.main()
