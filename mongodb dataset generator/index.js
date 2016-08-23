'use strict';
const fs = require('fs');
const chalk = require('chalk');
const mongoose = require('mongoose');
const ProgressBar = require('progress');
const Generator = require('./generator.js');

const seed = process.argv[3] || Date.now();
const generator = new Generator(seed);

const part = 10000;

// check argv length
if( process.argv.length < 3 ) {
    console.log( chalk.red('Usage: node index.js <count> <seed>') );
    process.exit();
}
const count = process.argv[2];

const Schema = mongoose.Schema;
const schema = require('./schema.js');
const data =  JSON.parse( fs.readFileSync('./data.json', 'utf8') );

const fieldsType = {
    email: 'Email',
    name: 'Name',
    password: 'Password',
    path: 'Path',
    gender: 'Gender',
    number: 'Number',
    empty: 'Empty'
};

mongoose.Promise = global.Promise;
var dbConnection = mongoose.createConnection(`mongodb://localhost/${data.server.db}`);
dbConnection.on('error', function(error) {
    DEBUG(error);
    throw error;
});

dbConnection.model(data.server.collection,  new Schema(schema));
var item = dbConnection.model(data.server.collection);

var len = parseInt(count, 10);

var bar = new ProgressBar('Insert   [:bar] :percent', {
    complete: '=',
    incomplete: ' ',
    width: 30,
    total: len
});

var bar2 = new ProgressBar('Generate [:bar] :percent', {
    complete: '=',
    incomplete: ' ',
    width: 30,
    total: len
});

function newItem( itemInfo ) {

    item(itemInfo).save( function(err) {
        if(err) {
            console.log( chalk.red(err) );
            process.exit();
        }
        bar.tick();
        if (bar.complete) {
            console.log('complete');
            process.exit();
        }
    });

};

try {
    for (let i = 1; i <= count; i++) {
        newItem( generator.newItem(data.dataset) );
        bar2.tick();
    }
} catch (e) {
    console.log( chalk.red(e) );
    process.exit();
}
