'use strict';

var bindings = require('bindings');
var keybindings =  bindings('keybindings');

keybindings.listen(function () {
  console.log('key pressed');
});
/*
var Keybinding = function(options) {
  options = options || {};

  if (!options.key) {
    throw "key binding must be defined";
  }

  if (!options.keydown && !options.keyup) {
    throw "At least one event should be defined";
  }

  var keys = options.key.split('+');

  var key = keys[keys.length - 1];
  keys.length -= 1;
};

module.exports = Keybinding;*/


setInterval(function () {
  console.log('alive');
}, 2000);
console.log('Done');