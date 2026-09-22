"""py_test that imports the pybind_extension and calls into C++."""

import unittest

from python import fastmath


class FastmathTest(unittest.TestCase):
    def test_add(self):
        self.assertEqual(fastmath.add(2, 40), 42)

    def test_counter(self):
        c = fastmath.Counter()
        c.increment(3)
        c.increment(4)
        self.assertEqual(c.value, 7)


if __name__ == "__main__":
    unittest.main()
