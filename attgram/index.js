'use strict';
const telegramLink = require('telegram.link')();

var client = telegramLink.createClient(
    {
        id:  56970,
        hash: '5abd96ef7120e1213ba4b7c4c716e2cb',
        version: '1.0.0',
        lang: 'fa',
        deviceModel: 'cl',
        systemVersion: '1.0.0',
    }, function(err) {
        console.log('ok!');
    }
);
