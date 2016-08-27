'use strict';
const os = require('os');
const fs = require('fs');

////////////////////////////////////////////////////////////////////////////////
var myAuth = {
    "key": {
        "id": {
            "type": "Buffer",
            "data": [174, 29, 60, 162, 72, 248, 161, 113]
        },
        "value": {
            "type": "Buffer",
            "data": [189, 15, 252, 242, 217, 27, 47, 19, 161, 202, 144, 102, 58, 128, 66, 191, 24, 88, 211, 63, 186, 103, 8, 205, 235, 225, 179, 15, 230, 207, 214, 115, 239, 142, 15, 219, 164, 186, 199, 106, 251, 224, 134, 225, 226, 0, 218, 17, 139, 236, 119, 161, 27, 253, 27, 237, 163, 246, 65, 148, 58, 45, 132, 171, 130, 108, 185, 85, 78, 163, 137, 19, 217, 181, 18, 102, 36, 52, 242, 223, 151, 125, 138, 234, 148, 78, 54, 60, 181, 137, 130, 42, 239, 56, 208, 186, 203, 52, 71, 98, 132, 97, 47, 146, 123, 209, 242, 237, 30, 96, 253, 62, 57, 55, 119, 115, 74, 6, 242, 95, 238, 19, 175, 219, 139, 1, 181, 56, 237, 225, 24, 115, 156, 196, 252, 166, 117, 61, 76, 86, 135, 105, 56, 44, 163, 51, 198, 229, 207, 113, 109, 159, 144, 121, 226, 187, 22, 204, 53, 235, 135, 196, 159, 10, 238, 5, 94, 191, 65, 147, 239, 230, 103, 86, 71, 227, 18, 184, 109, 42, 251, 71, 218, 3, 15, 130, 101, 182, 22, 27, 104, 161, 40, 6, 144, 114, 65, 120, 154, 182, 240, 34, 171, 227, 130, 255, 57, 97, 67, 73, 120, 158, 230, 40, 99, 249, 197, 28, 180, 157, 66, 66, 70, 159, 216, 72, 68, 110, 154, 43, 126, 191, 95, 101, 103, 84, 86, 188, 31, 251, 169, 223, 184, 41, 99, 11, 109, 185, 59, 71, 216, 34, 229, 191, 133, 62]
        }
    },
    "serverSalt": {
        "type": "Buffer",
        "data": [235, 166, 175, 183, 74, 80, 218, 184]
    }
};
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
    systemVersion: os.platform()+'/'+os.release()
}

function getDialogs(client) {
    console.log('getDialogs!');
    client.messages.getDialogs(0, -1, 10, function(data) {

        console.log('&&&&&&&&&&&&&&&&&&&&&&&');
        console.log(data);
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
            getDialogs(client);
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

        getContacts(client)

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

        // client.createAuthKey(function(auth){
        //
        //     data.user = {};
        //     data.user.phone = '00989333564933';
        //     data.app.authKey = auth.key.encrypt('123');
        //
        //     client.auth.sendCode(data.user.phone, 5, 'en',function(result){
        //         console.log('try to send code');
        //         console.log('Res:',JSON.stringify(result));
        //
        //         if(result.instanceOf('mtproto.type.Rpc_error')){
        //
        //             if(result.error_code === 303){ // PHONE_MIGRATE_X error (wrong datacenter)
        //                 console.log('wrong datacenter');
        //                 console.log('Finding Datacenter...')
        //
        //                 client.getDataCenters( function(dcs) {
        //                     data.dataCenters = dcs;
        //                     data.dataCenter = data.dataCenters['DC_'+result.error_message.slice(-1) || data.dataCenters.nearest];
        //                     client.end(function(){
        //                         data.connect(true);
        //                     });
        //                 });
        //
        //             } else {
        //                 console.log('bad error!');
        //             }
        //
        //         } else { // NO ERROR
        //
        //             console.log('auth generated!');
        //             fs.writeFile('key3.json', JSON.stringify(auth), function(err){
        //               if(err) console.log('FATAL: Could not write key to disk:',err)
        //             })
        //
        //             fs.writeFile('key3', data.app.authKey, function(err){
        //               if(err) console.log('FATAL: Could not write key to disk:',err)
        //             })
        //
        //             console.log('no error!');
        //             data.user.registered = result.phone_registered;
        //             data.user.phoneCodeHash = result.phone_code_hash;
        //
        //             if(!data.user.registered){
        //                 console.log( "Your number ("+data.user.phone+") is not registered.\nTelecommander will register your account with the Telegram service." );
        //             } else {
        //                 console.log( "Your number ("+data.user.phone+") is already assigned to a Telegram account.\nTelecommander will log you in." );
        //             }
        //
        //             console.log( 'Your telegram code:','',data.onPhoneCode );
        //
        //             console.log('--------------------------------------');
        //             getCode( client, result.phone_code_hash );
        //
        //         }
        //     });
        // });


    });

}

fs.readFile('key4', function(err, content) {
    data.app.authKey = telegramLink.retrieveAuthKey(content, '123');
    console.log(data.app.authKey);
    data.connect();
});


process.stdin.on('readable', () => {
    var chunk = process.stdin.read();
    if (chunk !== null) {

        console.log(JSON.stringify(data.user));
    }
});
