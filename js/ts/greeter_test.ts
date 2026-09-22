// Compiled by the same ts_project and executed by js_test.
import { strict as assert } from 'node:assert';
import { makeGreeter, sum } from './greeter';

const g = makeGreeter('Bazel');
assert.equal(g.name, 'Bazel');
assert.equal(g.greet(), 'Hello, Bazel from TypeScript!');
assert.equal(sum([1, 2, 3]), 6);

console.log('js/ts/greeter_test.ts: ok');
