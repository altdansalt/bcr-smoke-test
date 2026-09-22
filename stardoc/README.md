# stardoc — stardoc 0.8.1

Exercises: `stardoc(input = "//skylib:greeting.bzl", deps = [bzl_library])` generating Markdown
for a rule, a provider, a macro and two functions, plus a `diff_test` against the committed
golden `greeting_docs.golden.md`. Regenerate the golden with
`bazel build //stardoc:greeting_docs && cp bazel-bin/stardoc/greeting_docs.md stardoc/greeting_docs.golden.md`.

All code written for this repo.
