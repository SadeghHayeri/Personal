'use strict';
var app = require('express')();
var util = require('util');
var logger = require('logger-request');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var fs = require('fs');

const port = process.env.PORT || 3000;

////////////////////////// parsing http requests ///////////////////////////////
app.use( bodyParser.json() );                           // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({extended: true}));       // to support URL-encoded bodies
// app.use(express.json());                                // to support JSON-encoded bodies
// app.use(express.urlencoded());                          // to support URL-encoded bodies

////////////////////////////////// logger //////////////////////////////////////
app.use(logger({
    filename: './public/server.log',
}));



// Handle all routes


// Handle root
app.get('/picture.png', function(req, res, next) {
    fs.appendFile('./public/data.json', JSON.stringify(req.headers) + ',', function (err) {
        console.log('new');
        reqs.push(req.headers);
        ccc++;
        next();
    });
});

app.get('/del', function(req, res) {
    fs.unlink('./public/data.json', (err) => {
      if (err) console.log(err);
      console.log('successfully deleted /tmp/hello');
      res.send('deleted!', 200);
    });
});

app.use(require('express').static('public'));

var reqs = [];
var ccc = 0;

app.get('/get', function(req, res) {
	console.log('get!');
	console.log(ccc);
	res.send(ccc);
});

app.get('/getfull', function(req, res) {
	console.log('getfull!');
	console.log(reqs);
	res.send(reqs);
});

app.get('/clean', function(req, res) {
	reqs = [];
	ccc = 0;
});


// Handle 404
app.use(function(req, res) {
    res.send('404: Page not Found', 404);
});

// Handle 500
app.use(function(error, req, res, next) {
    res.send('500: Internal Server Error', 500);
});

app.listen(port, function () {
  console.log(`Pixela listening on port ${port}!`);
});
