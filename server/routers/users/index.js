const router = require('express').Router()
const User = require('../../models/User')
const bcrypt = require('bcrypt')
const { auth, ROLES } = require('../auth');

// CREATE NEW USER
// METHOD: POST
// PATH: /users
// BODY: {"email": "email", "password": "password"}
router.post('/', async (req, res) => {
	// input validation
	const { firstname, lastname, email, password } = req.body
	if (!email || !password || !firstname || !lastname) {
		return res.status(422)
	}
	try {
		// create password hash
		const hash = await bcrypt.hash(password, 8)
		// create user
		const user = new User({
			firstname,
			lastname,
			email,
			password: hash,
			_role: 'basic'
		})
		// save user
		if (await user.save()) return res.sendStatus(201)
		else res.sendStatus(200)
	} catch (e) {
		// user conflict
		if (e.code === 11000) return res.sendStatus(409)
		else return res.sendStatus(500)
	}
})

// DELETE USER
// Method: POST
// Path: /users
// Params: ?_id=ObjectId()
router.delete('/', auth, async (req, res) => {
	const { _id } = req.params
	if (!_id) return res.sendStatus(422)
	if (res.locals._role !== ROLES.admin) {
		if (res.locals._id !== _id) return res.sendStatus(403)
	}
	try {
		await User.findByIdAndDelete(_id)
		return res.sendStatus(200)
	} catch (e) {
		console.log(e)
		return res.sendStatus(500)
	}
})

module.exports = router