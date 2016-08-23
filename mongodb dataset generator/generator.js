'use strict';
var Chance = require('chance');

class generator {

    constructor( seed ) {
        this.chance = new Chance(seed);
    }

    newItem( dataset ) {

        var item = {};
        for (var i = 0; i < Object.keys(dataset).length; i++) {

            switch (dataset[ Object.keys(dataset)[i] ]) {
                case 'Username':
                    item[ Object.keys(dataset)[i] ] = this.chance.word({length:50});
                    break;
                case 'Email':
                    item[ Object.keys(dataset)[i] ] = this.chance.word({length:50}) + this.chance.email();
                    break;
                case 'Name':
                    item[ Object.keys(dataset)[i] ] = this.chance.name();
                    break;
                case 'Password':
                    item[ Object.keys(dataset)[i] ] = this.chance.string({length:40});
                    break;
                case 'Image':
                    item[ Object.keys(dataset)[i] ] = this.chance.url({extensions: ['gif', 'jpg', 'png']})
                    break;
                case 'Gender':
                    item[ Object.keys(dataset)[i] ] = this.chance.gender()
                    break;
                case 'Number':
                    item[ Object.keys(dataset)[i] ] = this.chance.natural({min: 0, max: 1000});
                    break;
                case '[Id]':
                    item[ Object.keys(dataset)[i] ] = this.chance.n(this.chance.word, this.chance.natural({min: 0, max: 10}), { length: 24 });
                    break;
                default:
                    if( typeof (dataset[ Object.keys(dataset)[i] ]) === 'object' )
                        item[ Object.keys(dataset)[i] ] = this.newItem( dataset[Object.keys(dataset)[i]] );
                    else
                        throw new Error(`BadType(${dataset[ Object.keys(dataset)[i] ]})`);
            }

        }
        return item;
    };
}

module.exports = generator;
