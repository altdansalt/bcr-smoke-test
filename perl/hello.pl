use strict;
use warnings;

use perl::greeter;

my $name = @ARGV ? $ARGV[0] : "World";
print greeter::greet($name), "\n";
