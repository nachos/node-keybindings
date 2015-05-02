'use strict';

var bindings = require('bindings');
var KeybindingsEmitter =  bindings('keybindings').KeybindingsEmitter;
var events = require('events');

inherits(KeybindingsEmitter, events.EventEmitter);
// exports.KeybindingsEmitter = KeybindingsEmitter;

// extend prototype
function inherits(target, source) {
  for (var k in source.prototype)
    target.prototype[k] = source.prototype[k];
}

var emitter = new KeybindingsEmitter();
module.exports = emitter;