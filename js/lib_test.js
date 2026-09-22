// js_test entry point: plain node assertions against lib.js and its npm deps.
const assert = require('node:assert/strict');
const _ = require('lodash');
const { greeting, newId, isValidId } = require('./lib');

assert.equal(greeting('bazel'), 'Hello, Bazel!');
assert.ok(isValidId(newId()), 'uuid.v4 should produce a valid uuid');
assert.equal(isValidId('not-a-uuid'), false);
assert.deepEqual(_.chunk([1, 2, 3, 4], 2), [[1, 2], [3, 4]]);
assert.ok(process.version.startsWith('v22.'), `expected node 22 from rules_nodejs, got ${process.version}`);

console.log('js/lib_test.js: ok');
