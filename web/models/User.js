const mongoose = require('mongoose')
const bcrypt = require('bcrypt')

const UserSchema = mongoose.Schema({
	email: {
		type: String,
		unique: true,
	},
	password: String
}, {
	timestamps: { createdAt: 'created_at' }
})


module.exports = mongoose.model('User', UserSchema)