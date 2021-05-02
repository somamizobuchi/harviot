const mongoose = require('mongoose')
const bcrypt = require('bcrypt')

const PlantSchema = mongoose.Schema({
	name: {
		type: String,
		default: ""
	},
	info: {
		family: {
			type: String,
			default: "",
			required: true
		},
		variety: {
			type: String,
			default: "",
			required: true
		}
	},
	password: {
		type: String,
		required: true
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

PlantSchema.pre('save', async (next) => {
	this.password = await bcrypt.hash(this.password, 12)
})

module.exports = mongoose.model('Plant', PlantSchema)