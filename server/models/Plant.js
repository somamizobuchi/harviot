const mongoose = require('mongoose')
const bcrypt = require('bcrypt')

const PlantSchema = mongoose.Schema({
	name: {
		type: String,
		trim: true
	},
	password: {
		type: String
	}
}, {
	timestamps: {
		createdAt: 'created_at',
		updatedAt: 'updated_at'
	}
})

module.exports = mongoose.model('Plant', PlantSchema)