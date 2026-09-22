"""A tiny rule and macro built on bazel_skylib's `lib/` helpers (paths, dicts, selects).

Written for bcr-smoke-test; patterned after the examples in
https://github.com/bazelbuild/bazel-skylib/tree/main/docs (Apache-2.0).
"""

load("@bazel_skylib//lib:dicts.bzl", "dicts")
load("@bazel_skylib//lib:paths.bzl", "paths")
load("@bazel_skylib//lib:selects.bzl", "selects")

DEFAULT_STYLE = {"greeting": "Hello", "punctuation": "!"}

GreetingInfo = provider(
    doc = "Carries the rendered greeting line.",
    fields = {"line": "The greeting text without a trailing newline."},
)

def greeting_line(who, style = {}):
    """Returns e.g. `Hello, who!`; `style` overrides keys of `DEFAULT_STYLE` (via `dicts.add`).

    Args:
      who: who to greet.
      style: dict with optional `greeting` / `punctuation` overrides.

    Returns:
      The greeting string.
    """
    s = dicts.add(DEFAULT_STYLE, style)
    return "{}, {}{}".format(s["greeting"], who, s["punctuation"])

def greeting_out_name(name):
    """Returns the output file name for a `greeting_file` target: `<name>` with a `.txt` extension.

    Args:
      name: the target name.

    Returns:
      The basename of the output (uses `paths.replace_extension`).
    """
    return paths.replace_extension(paths.basename(name), ".txt")

def _greeting_file_impl(ctx):
    out = ctx.actions.declare_file(greeting_out_name(ctx.label.name))
    line = greeting_line(ctx.attr.who, ctx.attr.style)
    ctx.actions.write(out, line + "\n")
    return [DefaultInfo(files = depset([out])), GreetingInfo(line = line)]

greeting_file = rule(
    implementation = _greeting_file_impl,
    doc = "Writes `<greeting>, <who><punctuation>` to `<name>.txt`.",
    attrs = {
        "who": attr.string(mandatory = True, doc = "Who to greet."),
        "style": attr.string_dict(doc = "Overrides for `DEFAULT_STYLE`."),
    },
)

def greeting_for_os(name, **kwargs):
    """Macro: a `greeting_file` whose `who` is chosen with `selects.with_or` on the target OS.

    Args:
      name: target name.
      **kwargs: forwarded to `greeting_file`.
    """
    greeting_file(
        name = name,
        who = selects.with_or({
            ("@platforms//os:linux", "@platforms//os:macos"): "POSIX",
            "@platforms//os:windows": "Windows",
            "//conditions:default": "stranger",
        }),
        **kwargs
    )
