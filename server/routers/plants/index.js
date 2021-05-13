const router = require('express').Router()
const { auth, verifyRole, ROLES } = require('../auth')
const Plant = require('../../models/Plant')
const User = require('../../models/User')
const bcrypt = require('bcrypt')
const logsRouter = require('./logs')
const imagesRouter = require('./images')

// Plant logs
router.use('/logs', logsRouter)
// Plant images
router.use('/images', imagesRouter)

// Get Plant settings
router.get('/', auth, (req, res) => {
	Plant.findById(res.locals._id)
		.select('name')
		.exec((err, res) => {
			if(err) return res.sendStatus(500)
			return res.status(200).json()
		})
})

// Create New Plant
router.post('/', auth, verifyRole(ROLES.admin), async (req, res) => {
	const { name, password, info } = req.body
	try {
		let plant = new Plant({
			name,
			password,
			info: {
				family: info.family,
				variety: info.variety
			}
		})
		await plant.save()
	} catch (err) {
		let code;
		let messages = err.errors && Object.values(err.errors).map(function(e){
			let message;
			switch(e.name){
				case 'CastError':
					message = `The '${e.path}' field is not formatted correctly`
					break
				case 'ValidatorError':
					message = `Missing '${e.path}' field`
					code = code > 422 ? code : 422
					break
				default:
					message = `Unknown error`
					code = 500
			}
			return message
		})
		return res.status(code).send({messages})
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