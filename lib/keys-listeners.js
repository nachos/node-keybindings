'use strict';

var _ = require('lodash');

var keysUpListeners = {};
var keysDownListeners = {};

var newKeydown = function (combo, downCallback, upCallback) {
  return function () {
    if (upCallback && combo.split('+').length > 1) {
      var comboParts = combo.split('+');

      _.forEach(comboParts, function (part) {
        if (!keysUpListeners[part]) {
          keysUpListeners[part] = [];
        }

        keysUpListeners[part].push(function () {
          var self = this;

          _.forEach(comboParts, function (part2) {
            keysUpListeners[part2].splice(keysUpListeners[part2].indexOf(self), 1);
          });

          upCallback();
        });
      });
    }

    downCallback();
  }
};

var registerCombo = function (combo, downCallback, upCallback) {
  if (!keysDownListeners[combo]) {
    keysDownListeners[combo] = [];
  }

  var keydownInternal, keyupInternal;

  if (combo.split('+').length === 1) {
    keydownInternal = downCallback;

    if (!keysUpListeners[combo]) {
      keysUpListeners[combo] = [];
    }

    keyupInternal = upCallback;
    keysUpListeners[combo].push(keyupInternal);
  } else {
    keydownInternal = newKeydown(combo, downCallback, upCallback);
  }

  keysDownListeners[combo].push(keydownInternal);

  return function () {
    if (keysDownListeners[combo] && keysDownListeners[combo].indexOf(keydownInternal) != -1) {
      keysDownListeners[combo].splice(keysDownListeners[combo].indexOf(keydownInternal), 1);
    }

    if (keyupInternal && keysUpListeners[combo] && keysUpListeners[combo].indexOf(keyupInternal) != -1) {
      keysDownListeners[combo].splice(keysDownListeners[combo].indexOf(keyupInternal), 1);
    }
  }
};

exports.registerCombo = registerCombo;

exports.activateKeyUp = function (key) {
  if (keysUpListeners[key]) {
    _.forEach(keysUpListeners[key], function (callback) {
      callback();
    })
  }
};

exports.activateKeyDown = function (combo) {
  if (keysDownListeners[combo]) {
    _.forEach(keysDownListeners[combo], function (callback) {
      callback();
    })
  }
};