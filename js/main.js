// js_binary entry point: prints a greeting for each argument (deterministic output).
const { greeting } = require('./lib');

const names = process.argv.slice(2);
for (const name of names.length ? names : ['bazel']) {
  console.log(greeting(name));
}
