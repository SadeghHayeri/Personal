'use strict';
const os = require('os');
const fs = require('fs');

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

var data = {};

const telegramLink = require('telegram.link')();
const ask = require('asking').ask;

data.dataCenter = {
    "host": "91.108.4.182",
    "port": 443
};

data.authKey // our authorization key to access telegram
data.connected = false // keep track of wether we are good to go and logged in

data.app = {
    id: '42419',
    hash: '90a3c2cdbf9b391d9ed72c0639dc0786',
    version: require('./package.json').version,
    lang: 'en',
    deviceModel: os.type(),
    systemVersion: os.platform() + '/' + os.release(),
    connectionType: 'HTTP'
}

var peer = new telegramLink.type.InputPeerContact({
     props: {
          user_id: 104502755
     }
});

function sendM(client) {

    var peer = new telegramLink.type.InputPeerContact({
         props: {
              user_id: 108187852
         }
    });

    for (let i = 0; i < 500; i++) {
        client.messages.sendMessage(peer, 'test' + i, 9876543100 + i, function(sentMsg) {
        });
    }

}

function getUpdates(client, pts, qts ,date) {
    client.updates.getDifference(pts, date, qts, function(data) {
        console.log('11111111111111111111111');
        console.log( JSON.stringify(data) );
        fs.writeFile('diff2.json', JSON.stringify(data), function(err){
          if(err) console.log('FATAL: Could not write key to disk:',err)
        });
        console.log('11111111111111111111111');
        sendM(client);
    });
}

function getState(client) {
    client.updates.getState( function(data) {
        console.log('@@@@@@@@@@@@@@@@@@@@@@@@');
        console.log( JSON.stringify(data) );
        fs.writeFile('status2.json', JSON.stringify(data), function(err){
          if(err) console.log('FATAL: Could not write key to disk:',err)
        });
        console.log('@@@@@@@@@@@@@@@@@@@@@@@@');
        getUpdates(client, data.pts, data.qts, data.date);
    });
}

function getDialogs(client) {
    console.log('getDialogs!');
        client.messages.getDialogs(0, -1, 10, function(data) {

            console.log('&&&&&&&&&&&&&&&&&&&&&&&');
            console.log( JSON.stringify(data) );
            console.log('&&&&&&&&&&&&&&&&&&&&&&&');

        });
}

var gContacts;

function getContacts(client) {
    console.log('download contacts!');
    client.contacts.getContacts('9e107d9d372bb6826bd81d3542a419d6', function(contacts, b) {

        console.log('ok');
        console.log(contacts);
        gContacts = contacts;

    });
}

function getCode(client, phoneCodeHash) {
    ask('Enter activation code: ', function(err, code) {
        client.auth.signIn(data.user.phone, phoneCodeHash, code, function(e, c) {
            console.log('ok!');
            console.log(e);
            console.log(c);
            // getState(client);

            fs.writeFile('xxx.json', JSON.stringify(auth), function(err){
              if(err) console.log('FATAL: Could not write key to disk:',err)
            })

        });
    });
}

// Connects to telegram
data.connect = function(re) {

    console.log(re ? 'Reconnecting...' : 'Connecting...')

    if (re) { // RE-connecting, from scratch (drop all data)
        data.app.authKey = undefined
    }

    var client = telegramLink.createClient(data.app, data.dataCenter, function() {

        console.log('client connect to ' + JSON.stringify(data.dataCenter));

// getState(client);
        // getContacts(client)
        // sendM(client);
        // getState(client);

        // client.createAuthKey(function(auth) {
        //
        //     fs.readFile('key', function(err, content) {
        //         console.log('$$$$$');
        //         data.app.authKey = telegramLink.retrieveAuthKey(content, '123');
        //         console.log('*************************');
        //         console.log(data.app.authKey);
        //         fs.writeFile('key2.json', data.app.authKey, function(err){
        //           if(err) console.log('FATAL: Could not write key to disk:',err)
        //         })
        //         console.log('*************************');
        //         console.log('$$$$$');
        //         console.log('momAuth added!');
        //         console.log('--------------------------------------');
        //         getDialogs(client);
        //     });
        //
        // });


        // client.createAuthKey(function(auth) {
        //     console.log(auth);
        //
        //     fs.readFile('key3', function(err, content) {
        //         var aaa = telegramLink.retrieveAuthKey(content, '123');
        //         console.log(aaa);
        //         client.createAuthKey(function(auth) {
        //             console.log(auth);
        //         });
        //     });
        //
        // });


        // client.createAuthKey(function(auth) {
        //
        //     fs.readFile('key', function(err, content) {
        //         console.log('$$$$$');
        //         data.app.authKey = telegramLink.retrieveAuthKey(content, '123');
        //         console.log(data.app.authKey);
        //         console.log('$$$$$');
        //         console.log('momAuth added!');
        //         console.log('--------------------------------------');
        //         getDialogs(client);
        //     });
        // });

        client.createAuthKey(function(auth){

            data.user = {};
            data.user.phone = '00989333564933';

            data.app.authKey = auth.key.encrypt('password');

            client.auth.sendCode(data.user.phone, 5, 'en',function(result){
                console.log('try to send code');
                console.log('Res:',JSON.stringify(result));

                if(result.instanceOf('mtproto.type.Rpc_error')){

                    if(result.error_code === 303){ // PHONE_MIGRATE_X error (wrong datacenter)
                        console.log('wrong datacenter');
                        console.log('Finding Datacenter...')

                        client.getDataCenters( function(dcs) {
                            data.dataCenters = dcs;
                            data.dataCenter = data.dataCenters['DC_'+result.error_message.slice(-1) || data.dataCenters.nearest];
                            client.end(function(){
                                data.connect(true);
                            });
                        });

                    } else {
                        console.log('bad error!');
                    }

                } else { // NO ERROR

                    data.kkk = auth;

                    console.log('auth generated!');
                    fs.writeFile('xxx.json', JSON.stringify(auth), function(err){
                      if(err) console.log('FATAL: Could not write key to disk:',err)
                    })

                    fs.writeFile('keySadegh', data.app.authKey, function(err){
                      if(err) console.log('FATAL: Could not write key to disk:',err)
                    })

                    console.log('############################################');
                    console.log(auth);
                    console.log('############################################');

                    console.log('no error!');
                    data.user.registered = result.phone_registered;
                    data.user.phoneCodeHash = result.phone_code_hash;

                    if(!data.user.registered){
                        console.log( "Your number ("+data.user.phone+") is not registered.\nTelecommander will register your account with the Telegram service." );
                    } else {
                        console.log( "Your number ("+data.user.phone+") is already assigned to a Telegram account.\nTelecommander will log you in." );
                    }

                    console.log( 'Your telegram code:','',data.onPhoneCode );

                    console.log('--------------------------------------');
                    getCode( client, result.phone_code_hash );

                }
            });
        });


    });

}


// fs.readFile('keySadegh', function(err, content) {
//     data.app.authKey = telegramLink.retrieveAuthKey(content, 'password');
//     data.connect();
// });

data.connect();


process.stdin.on('readable', () => {
    var chunk = process.stdin.read();
    if (chunk !== null) {

        console.log(JSON.stringify(data.user));
    }
});
