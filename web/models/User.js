const mongoose = require('mongoose')
const bcrypt = require('bcrypt')

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

UserSchema.statics.login = function (email, password) {
	return new Promise((resolve, reject) => {
		this.find({ email }, async (err, user) => {
			if (err) return reject(err)
			if (!user) return resolve(null)
			try {
				var match = await bcrypt.compare(password, user.password)
			} catch (err) {
				return reject(err)
			}
			if (!match) return resolve(null)
			return resolve(user)
		})
	})
}

module.exports = mongoose.model('User', UserSchema)