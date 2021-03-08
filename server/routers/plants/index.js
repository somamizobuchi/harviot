const router = require('express').Router()
const { auth, verifyRole, ROLES } = require('../auth')
const Plant = require('../../models/Plant')
const User = require('../../models/User')
const bcrypt = require('bcrypt')

// Create New Plant
router.post('/', auth, verifyRole(ROLES.admin), async (req, res) => {
	const { name, password } = req.body
	if (!password) return res.sendStatus(422)
	const hash = await bcrypt.hash(password, 8)
	const plant = new Plant({
		name,
		password: hash
	})
	try {
		await plant.save()
	} catch (err) {
		console.log(err)
		return res.sendStatus(500)
	}
	return res.sendStatus(200)
})

router.delete('/:plant_id', auth, verifyRole(ROLES.admin), async (req, res) => {
	var plantId;
	if (!(plantId = req.params.plant_id)) {
		if (!(plantId = req.query.plant_id)) {
			if (!(plantId = req.body.plant_id)) {
				res.sendStatus(422)
			}
		}
	}
	Plant.deleteOne({ _id: plantId })
		.exec()
		.then(res => {
			if (res.nRemoved === 0) return res.sendStatus(304)
			return res.sendStatus(200)
		})
		.catch(err => {
			console.log(err)
			return res.sendStatus(500)
		})
})

module.exports = router