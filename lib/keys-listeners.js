'use strict';

var _ = require('lodash');

var keysUpListeners = {};
var keysDownListeners = {};

var registerCombo = function (combo, downCallback, upCallback) {
  if (!keysDownListeners[combo]) {
    keysDownListeners[combo] = [];
  }

  keysDownListeners[combo].push(function () {
    if (upCallback) {
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
  });
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