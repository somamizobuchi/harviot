const mongoose = require('mongoose')

const UserSchema = mongoose.Schema({
	email: {
		type: String,
		unique: true,
		trim: true,
		lowercase: true
	},
	password: String,
}, {
	timestamps: {
		createdAt: 'created_at',
		updatedAt: 'updated_at'
	}
})

module.exports = mongoose.model('User', UserSchema)