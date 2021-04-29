const mongoose = require('mongoose')

const LogSchema = mongoose.Schema({
    date: {
        type: Date,
        default: Date.now
    },
    sensorValues: {
        temperature: {
            type: Number,
            default: 0
        },
        humidity: {
            type: Number,
            default: 0
        },
        ambient_light: {
            type: Number,
            default: 0
        }
    }
})

module.exports = mongoose.model('Log', LogSchema)