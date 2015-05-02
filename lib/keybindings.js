'use strict';

var bindings = require('bindings');
var keybindings =  bindings('keybindings');
var listeners = require('./keys-listeners');
var vk = require('./virtual-keys');

function isKeyDown (keys, keyName) {
  return keys[vk.getCode(keyName)];
}

function keyUp (keys, key) {
  var keyName = vk.getName(key);
  listeners.activateKeyUp(keyName);
}

function keyDown (keys, key) {
  var combo = '';

  if (isKeyDown(keys, 'ctrl'))
    combo += 'ctrl+';

  if (isKeyDown(keys, 'lwin') || isKeyDown(keys, 'rwin'))
    combo += 'win+';

  if (isKeyDown(keys, 'alt'))
    combo += 'alt+';

  if (isKeyDown(keys, 'shift'))
    combo += 'shift+';

  var keyName = vk.getName(key);
  combo += keyName;

  listeners.activateKeyDown(keyName);

  if (keyName !== combo) {
    listeners.activateKeyDown(combo);
  }
}

var beforeKeys = keybindings.getKeyboardState().keys;
setInterval(function () {
  var keys = keybindings.getKeyboardState().keys;

  for (var key = 0; key < keys.length; key++){
    if (keys[key] !== beforeKeys[key] && ((beforeKeys[key] == false || keys[key] == false))){
      if (keys[key]) {
        keyDown(keys, key);
      } else {
        keyUp(keys, key);
      }
    }
  }

  beforeKeys = keys;
}, 100);

var Keybinding = function(options) {
  options = options || {};

  if (!options.key) {
    throw "key binding must be defined";
  }

  if (!options.keydown && !options.keyup) {
    throw "At least one event should be defined";
  }

  listeners.registerCombo(options.key, options.keydown || function () {}, options.keyup);
};

module.exports = Keybinding;

var test = new Keybinding({
  key: 'ctrl+shift+p',
  keyddown: function () {
    console.log('I was pressed!!');
  },
  keyup: function () {
    console.log('Im up');
  }
});