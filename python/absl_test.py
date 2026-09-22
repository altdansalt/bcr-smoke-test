"""abseil-py smoke: absltest + absl.flags."""

from absl import flags
from absl.testing import absltest

from python import greeter

FLAGS = flags.FLAGS
flags.DEFINE_string("name", "absl", "Who to greet.")
flags.DEFINE_integer("times", 2, "How many greetings.", lower_bound=1)


class AbslGreeterTest(absltest.TestCase):
    def test_flag_defaults(self):
        self.assertEqual(FLAGS.name, "absl")
        self.assertEqual(FLAGS.times, 2)

    def test_greet_with_flags(self):
        greetings = [greeter.greet(FLAGS.name) for _ in range(FLAGS.times)]
        self.assertLen(greetings, 2)
        self.assertEqual(greetings[0], "Hello, absl!")

    def test_flag_validation(self):
        with self.assertRaises(flags.IllegalFlagValueError):
            FLAGS.times = 0


if __name__ == "__main__":
    absltest.main()
