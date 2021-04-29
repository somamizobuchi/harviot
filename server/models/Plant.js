const mongoose = require('mongoose')

const PlantSchema = mongoose.Schema({
	name: {
		type: String,
		default: "",
		trim: true,
	},
	password: {
		type: String,
		required: true
	},
	owner: {
		type: mongoose.Schema.Types.ObjectId,
		default: null,
		ref: 'User'
	},
	logs: [{
		type: mongoose.Schema.Types.ObjectId,
		ref: 'Log'
	}]
}, {
	timestamps: {
		createdAt: 'created_at',
		updatedAt: 'updated_at'
	}
})

module.exports = mongoose.model('Plant', PlantSchema)