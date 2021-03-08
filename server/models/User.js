const mongoose = require('mongoose')

const UserSchema = mongoose.Schema({
	email: {
		type: String,
		unique: true,
		trim: true,
		lowercase: true
	},
	password: String,
	_role: {
		type: String,
		enum: ['basic', 'admin'],
		default: 'basic'
	}
}, {
	timestamps: {
		createdAt: 'created_at',
		updatedAt: 'updated_at'
	}
})


module.exports = mongoose.model('User', UserSchema)