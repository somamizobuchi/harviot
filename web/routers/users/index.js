const router = require('express').Router()
const User = require('../../models/User')
const bcrypt = require('bcrypt')

router.post('/', async (req, res) => {
	const { email, password } = req.body
	if (!req.body.email | !req.body.password) {
		return res.status(422)
	}
	// encrypt 
	const hash = await bcrypt.hash(password, 8)

	// create user
	const user = new User({
		email: email,
		password: hash
	})
	// save user
	user.save(err => {
		if (err) {
			// User exists
			if (err.code === 11000) return res.sendStatus(409)
			return res.sendStatus(500)
		} else {
			return res.sendStatus(200)
		}
	})
})
module.exports = router