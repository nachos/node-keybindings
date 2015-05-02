'use strict';

var emitter = require('./event-emitter').Emitter;

var emitter = new Emitter();

emitter.on('ping', function () {
  console.log('ping');
});

setInterval(function () {
  console.log('alive');
}, 2000);

emitter.ping();