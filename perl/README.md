# perl — rules_perl 1.1.2

| Target | Rule |
| --- | --- |
| `//perl:greeter` | `perl_library` (`greeter.pm`) |
| `//perl:hello` | `perl_binary` using the library |
| `//perl:greeter_test` | `perl_test` (`Test::More`) using the library |
| `//perl:hello_test` | `sh_test` (rules_shell) that runs the `perl_binary` and checks its output |

rules_perl downloads a relocatable perl and registers its toolchains from its own
`MODULE.bazel`, so no extension usage is needed in the root module. Modules are
resolved from the workspace root, hence `use perl::greeter;`.

## Attribution

`greeter_test.t` follows `examples/fibonacci/fibonacci_test.t` from
<https://github.com/bazelbuild/rules_perl> (Apache-2.0); the rest is original.
