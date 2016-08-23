module.exports = {

    username: {
        type: String,
        validate: {
            validator: function(v) {
                return /^[A-Za-z][A-Za-z0-9_]{5,50}$/.test(v);
            },
            message: 'invalid username'
        },
        required: [true, 'username required']
    },

    emailAddress: {
        type: String,
        lowercase: true,
        validate: {
            validator: function(v) {
                return /^([a-z0-9_\.-]+)@([\da-z\.-]+)\.([a-z\.]{2,6})$/.test(v);
            },
            message: 'invalid emailAddress'
        },
        required: [true, 'emailAddress required']
    },

    nickname: {
        type: String,
        validate: {
            validator: function(v) {
                return (v.trim().length != 0);
            },
            message: 'invalid nickname'
        },
        required: [true, 'nickname required']
    },

    password: {
        type: String,
        required: [true, 'password required']
    },

    imagePath: {
        type: String,
        default: 'default-avatar.png'
    },

    gender: {
        type: String,
        enum: ["Male", "Female"],
        required: [true, 'gender required']
    },

    gameProfile:{
        gem: {
            type: Number,
            default: 0
        },
        coin: {
            type: Number,
            default: 0
        },
        gamesCount: {
            type: Number,
            default: 0
        },
        winCount: {
            type: Number,
            default: 0
        },
        score: {
            type: Number,
            default: 0
        }
    },

    achivements:[{ type: String }],

    createdAt: { type: Date, default: Date.now() },
    updatedAt: { type: Date, default: Date.now() },

    access: {
        banned: { type: Boolean, default: false },
        banReason: String,

        banHistory: [{
            banReason: String,
            banAt: Date,
            unbanAt: Date
        }]
    }

};
