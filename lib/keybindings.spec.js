'use strict';

var window = require('./keybindings');
var chai = require('chai');
var expect = chai.expect;

describe('keybindings', function () {

  describe('start', function() {

    it('return at least one window', function () {
      var windows = window.getAllWindows();
      expect(windows).to.have.length.above(0);
    });
  });
});