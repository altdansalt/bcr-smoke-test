# Adapted from rules_perl examples/fibonacci/fibonacci_test.t
# (https://github.com/bazelbuild/rules_perl, Apache-2.0).
use strict;
use warnings;

use Test::More tests => 2;

use perl::greeter;

is(greeter::greet("Bazel"), "Hello, Bazel!", "greets by name");
is(greeter::greet(""), "Hello, !", "handles an empty name");
