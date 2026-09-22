# js — aspect_rules_js, rules_nodejs, aspect_rules_ts

Smoke test for the JavaScript / TypeScript rulesets. All code here is original (no upstream
copies); the layout follows the aspect_rules_js and aspect_rules_ts docs.

## Modules and rules exercised

| Module | Version | What is used |
| --- | --- | --- |
| `rules_nodejs` | 6.7.5 | `node` module extension: `node.toolchain(node_version = "22.23.1")` pins the hermetic Node.js toolchain (root module wins over the defaults from rules_nodejs / rules_js). `//js:lib_test` asserts `process.version` is 22.x. |
| `aspect_rules_js` | 3.4.1 | `npm` extension (`npm_translate_lock` over the root `pnpm-lock.yaml`), `pnpm` extension (hermetic pnpm used to generate the lockfile), `npm_link_all_packages` (root `BUILD.bazel`), `js_library`, `js_binary`, `js_test`, `js_run_binary` (with `stdout` capture). |
| `aspect_rules_ts` | 3.10.1 | `typescript` extension (`deps(version_from = "//:package.json")`), `ts_project` with `transpiler = "tsc"` compiling `.ts` -> `.js` (plus the auto-generated `_typecheck_test`), consumed by a `js_test`. |

npm dependencies (root `package.json`): `lodash`, `uuid`, and dev deps `typescript`, `@types/node`.

## Targets

- `//js:lib` — `js_library` depending on `//:node_modules/lodash` and `//:node_modules/uuid`.
- `//js:hello` — `js_binary` (`main.js`), prints greetings.
- `//js:lib_test` — `js_test` running `lib_test.js` (node:assert against the lib and its npm deps).
- `//js:hello_txt` — `js_run_binary` running `:hello` at build time, stdout captured to `hello.txt`.
- `//js:hello_txt_test` — `diff_test` (bazel_skylib) of `hello.txt` vs `hello.expected.txt`.
- `//js/ts:greeter` — `ts_project` (`greeter.ts`, `greeter_test.ts`, `tsconfig.json`); also
  emits `//js/ts:greeter_typecheck_test`.
- `//js/ts:greeter_test` — `js_test` running the emitted `greeter_test.js`.

## Repo-root files owned by this package

`package.json`, `pnpm-lock.yaml`, `pnpm-workspace.yaml`, `.npmrc`, `.bazelignore` (must list
`node_modules`), and `npm_link_all_packages(name = "node_modules")` in the root `BUILD.bazel`.

Regenerate the lockfile after editing `package.json` (hermetic pnpm, no host node needed):

```
bazel run -- @pnpm//:pnpm --dir $PWD install --lockfile-only
```

## Gotchas

- rules_js 3.x + pnpm 10 refuse to load the lockfile unless lifecycle hooks are allow-listed:
  `pnpm-workspace.yaml` needs `allowBuilds: {}` (pnpm >= 10.26) or `onlyBuiltDependencies: []`.
- rules_ts 3.x: `ts_project` needs an explicit `transpiler = "tsc"` (or the flag
  `--@aspect_rules_ts//ts:default_to_tsc_transpiler`).
- The `ext` module-extension symbol of rules_ts is deprecated; use `typescript`.
- With `"types": []` in tsconfig, `@types/node` is not picked up; use `"types": ["node"]`.
