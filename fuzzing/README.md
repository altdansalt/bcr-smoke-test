# fuzzing — rules_fuzzing 0.8.0

| Target | Rule |
| --- | --- |
| `//fuzzing:kv_parser` | `cc_library` under test |
| `//fuzzing:kv_parser_test` | `cc_test` (googletest) sanity check |
| `//fuzzing:kv_parser_fuzz_test` | `cc_fuzz_test` with a committed seed corpus (`corpus/`) |

With rules_fuzzing's default engine (`@rules_fuzzing//fuzzing/engines:replay`)
`bazel test` simply replays every corpus file through `LLVMFuzzerTestOneInput`,
so the fuzz target runs as an ordinary hermetic test. The test launcher is a
Python program; rules_fuzzing's own `MODULE.bazel` declares the Python toolchains
and the `rules_fuzzing_py_deps` pip hub (hash-pinned `requirements.txt`), so the
only network access is at fetch time. To really fuzz, use e.g.
`--@rules_fuzzing//fuzzing:cc_engine=@rules_fuzzing//fuzzing/engines:libfuzzer`
with clang (see the rules_fuzzing README).

## Attribution

`kv_parser_fuzz_test.cc` starts from `examples/bzlmod/cc_fuzz_test.cc` in
<https://github.com/bazel-contrib/rules_fuzzing> (Apache-2.0); the parser is original.
