'use strict';
const cluster = require('cluster');
const fs = require('fs');
const chalk = require('chalk');
const mongoose = require('mongoose');
const ProgressBar = require('progress');
const Generator = require('./generator.js');
const numCPUs = require('os').cpus().length;

const seed = process.argv[3] || Date.now();
const generator = new Generator(seed);

const chunk = 50;

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

function newItem( itemInfo, done ) {

    item(itemInfo).save( function(err) {
        if(err) {
            console.log( chalk.red(err) );
            process.exit();
        }
        done();
    });

};

if (cluster.isMaster) {

    var len = parseInt(count*2, 10);
    var bar = new ProgressBar('[:bar] :percent :elapsed' , {
        complete: '=',
        incomplete: ' ',
        width: 50,
        total: len
    });

    for (var i = 0; i < numCPUs; i++)
        var w = cluster.fork();


    var allProgress = count;
    var inProgress = 0;
    function doWork() {
        if( allProgress ) {
            var eachWorker = ( Math.floor(allProgress/numCPUs) < chunk ) ? Math.floor(allProgress/numCPUs) : chunk;
            allProgress -= eachWorker * numCPUs;

            var lastCpu = (allProgress < numCPUs)? allProgress : 0;
            allProgress -= lastCpu;

            for (var id = 1; id < numCPUs; id++) {
                inProgress += eachWorker;
                cluster.workers[id].send( eachWorker );
            }
            inProgress += eachWorker + lastCpu;
            cluster.workers[numCPUs].send( eachWorker + lastCpu );
        }

    }
    doWork();

    var G = 0;
    var I = 0;
    cluster.on('message', function messageHandler(type) {

        if(type == 'G') G++;
        else I++;

        bar.tick();

        if( inProgress == G)
            doWork();

        if( I == count ) process.exit();

    });

    var thisWorker = Math.floor( count / numCPUs );
    Object.keys(cluster.workers).forEach(function(id) {
        // console.log('creating process with id = ' + cluster.workers[id].process.pid);

        //Catching errors
        cluster.workers[id].on('exit', function(code, signal) {
            if( signal ) {
                console.log("worker was killed by signal: "+signal);
            } else if( code !== 0 ) {
                console.log("worker exited with error code: "+code);
            } else {
                console.log("worker success!");
            }
        });

    });

    cluster.on('exit', (worker, code, signal) => {
        console.log(`worker ${worker.process.pid} died`);
    });

} else {


    // Notify master about the request
    process.on('message', function messageHandler(count) {
        try {
            for (var i = 0; i < count; i++) {
                process.send('G');
                newItem( generator.newItem(data.dataset), function() {
                     process.send('I');
                });
            }
        } catch (e) {
            console.log( chalk.red(e) );
            process.exit();
        }
    });


}
