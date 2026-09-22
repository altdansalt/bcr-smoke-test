// A tiny CommonJS library that depends on two npm packages linked by rules_js.
const _ = require('lodash');
const { v4: uuidv4, validate } = require('uuid');

function greeting(name) {
  return `Hello, ${_.capitalize(name)}!`;
}

function newId() {
  return uuidv4();
}

function isValidId(id) {
  return validate(id);
}

module.exports = { greeting, newId, isValidId };
