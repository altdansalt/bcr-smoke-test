# Loaded as `use perl::greeter;` -- rules_perl puts the workspace root on PERL5LIB.
use strict;
use warnings;

package greeter;

sub greet {
  my ($name) = @_;
  return "Hello, $name!";
}

1;
