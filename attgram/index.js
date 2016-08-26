'use strict';
const os = require('os');

var data = {};

const telegramLink = require('telegram.link')();
const ask = require('asking').ask;

data.dataCenter = {"host":"91.108.4.182","port":443};
data.authKey // our authorization key to access telegram
data.connected = false // keep track of wether we are good to go and logged in

process.stdin.on('readable', () => {
  var chunk = process.stdin.read();
  if (chunk !== null) {
    process.stdout.write(`data: ${chunk}`);
  }
});

data.app = {
    id: '56970',
    hash: '5abd96ef7120e1213ba4b7c4c716e2cb',
    version: require('./package.json').version,
    lang: 'en',
    deviceModel: os.type(),
    systemVersion: os.platform()+'/'+os.release()
};

function httpPoll( client ) {
    client.httpPoll( function(err, res) {

        console.log('-------');
        console.log(err);
        console.log('-------');
        console.log(res);
        console.log('-------');

    });
}

function getCode( client, phoneCodeHash ) {
    ask ('Enter activation code: ', function (err, code) {
        client.auth.signIn( data.user.phone, phoneCodeHash, code, function(e, c) {
            console.log('ok!');
            console.log(e);
            console.log(c);
            httpPoll(client);
        });
    });
}

// Connects to telegram
data.connect = function(re){

    console.log(re?'Reconnecting...':'Connecting...')

    if(re) { // RE-connecting, from scratch (drop all data)
        data.app.authKey = undefined
    }

    var client = telegramLink.createClient(data.app, data.dataCenter, function() {

        console.log('client created by ' + JSON.stringify(data.dataCenter));

        client.createAuthKey(function(auth){
            console.log('auth ky created!');

            data.user = {};
            data.user.phone = '+989333564933';
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

data.connect();

// var stdin = process.openStdin();
// stdin.addListener("data", function(d) {
//     console.log("you entered: [" +
//         d.toString().trim() + "]");
// });
