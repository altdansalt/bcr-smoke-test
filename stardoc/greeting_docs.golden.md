<!-- Generated with Stardoc: http://skydoc.bazel.build -->

A tiny rule and macro built on bazel_skylib's `lib/` helpers (paths, dicts, selects).

Written for bcr-smoke-test; patterned after the examples in
https://github.com/bazelbuild/bazel-skylib/tree/main/docs (Apache-2.0).

<a id="greeting_file"></a>

## greeting_file

<pre>
load("@bcr_smoke_test//skylib:greeting.bzl", "greeting_file")

greeting_file(<a href="#greeting_file-name">name</a>, <a href="#greeting_file-style">style</a>, <a href="#greeting_file-who">who</a>)
</pre>

Writes `<greeting>, <who><punctuation>` to `<name>.txt`.

**ATTRIBUTES**


| Name  | Description | Type | Mandatory | Default |
| :------------- | :------------- | :------------- | :------------- | :------------- |
| <a id="greeting_file-name"></a>name |  A unique name for this target.   | <a href="https://bazel.build/concepts/labels#target-names">Name</a> | required |  |
| <a id="greeting_file-style"></a>style |  Overrides for `DEFAULT_STYLE`.   | <a href="https://bazel.build/rules/lib/core/dict">Dictionary: String -> String</a> | optional |  `{}`  |
| <a id="greeting_file-who"></a>who |  Who to greet.   | String | required |  |


<a id="GreetingInfo"></a>

## GreetingInfo

<pre>
load("@bcr_smoke_test//skylib:greeting.bzl", "GreetingInfo")

GreetingInfo(<a href="#GreetingInfo-line">line</a>)
</pre>

Carries the rendered greeting line.

**FIELDS**

| Name  | Description |
| :------------- | :------------- |
| <a id="GreetingInfo-line"></a>line |  The greeting text without a trailing newline.    |


<a id="greeting_for_os"></a>

## greeting_for_os

<pre>
load("@bcr_smoke_test//skylib:greeting.bzl", "greeting_for_os")

greeting_for_os(<a href="#greeting_for_os-name">name</a>, <a href="#greeting_for_os-kwargs">**kwargs</a>)
</pre>

Macro: a `greeting_file` whose `who` is chosen with `selects.with_or` on the target OS.

**PARAMETERS**


| Name  | Description | Default Value |
| :------------- | :------------- | :------------- |
| <a id="greeting_for_os-name"></a>name |  target name.   |  none |
| <a id="greeting_for_os-kwargs"></a>kwargs |  forwarded to `greeting_file`.   |  none |


<a id="greeting_line"></a>

## greeting_line

<pre>
load("@bcr_smoke_test//skylib:greeting.bzl", "greeting_line")

greeting_line(<a href="#greeting_line-who">who</a>, <a href="#greeting_line-style">style</a>)
</pre>

Returns e.g. `Hello, who!`; `style` overrides keys of `DEFAULT_STYLE` (via `dicts.add`).

**PARAMETERS**


| Name  | Description | Default Value |
| :------------- | :------------- | :------------- |
| <a id="greeting_line-who"></a>who |  who to greet.   |  none |
| <a id="greeting_line-style"></a>style |  dict with optional `greeting` / `punctuation` overrides.   |  `{}` |

**RETURNS**

The greeting string.


<a id="greeting_out_name"></a>

## greeting_out_name

<pre>
load("@bcr_smoke_test//skylib:greeting.bzl", "greeting_out_name")

greeting_out_name(<a href="#greeting_out_name-name">name</a>)
</pre>

Returns the output file name for a `greeting_file` target: `<name>` with a `.txt` extension.

**PARAMETERS**


| Name  | Description | Default Value |
| :------------- | :------------- | :------------- |
| <a id="greeting_out_name-name"></a>name |  the target name.   |  none |

**RETURNS**

The basename of the output (uses `paths.replace_extension`).


