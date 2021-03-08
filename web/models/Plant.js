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

PlantSchema.statics.login = function (id, password) {
	return new Promise((resolve, reject) => {
		this.findById(id, async (err, plant) => {
			if (err) return reject(err)
			if (!plant) return resolve(null)
			try {
				var match = await bcrypt.compare(password, plant.password)
			} catch (err) {
				return reject(err)
			}
			if (!match) return resolve(null)
			return resolve(plant)
		})
	})
}

module.exports = mongoose.model('Plant', PlantSchema)