const router = require('express').Router()
const bcrypt = require('bcrypt')
const { signToken, verifyToken } = require('../../utils/jwt')
const User = require('../../models/User')

// Cookie-based auth middleware
const auth = (req, res, next) => {
	// Verify Token
	var data = verifyToken(req.cookies['auth'])
	if (!data) return res.sendStatus(403)
	res.locals._id = data._id
	return next()
}

// Authenticate User
router.get('/', auth, (req, res) => {
	return res.status(200).json({ _id: res.locals._id })
})

// User Login
router.post('/', async (req, res) => {
	// extract from query body
	const { email, password } = req.body
	// Input validation
	if (!email | !password) {
		console.log("not all details provided")
		return res.sendStatus(403)
	}

	try {
		// find user
		var user = await User.findOne({ email: email }).exec()
		// user doesn't exist
		if (!user) return res.sendStatus(404)
		// compare passwords
		if (!await bcrypt.compare(password, user.password))
			return res.sendStatus(403)
		// create token
		var token = await signToken({ _id: user._id })
	} catch (err) {
		return res.sendStatus(500)
	}
	// set cookie
	return res.cookie('auth', token).sendStatus(200)
})

// Logout
router.delete('/', (req, res) => {
	return res.clearCookie('auth').sendStatus(200)
})

module.exports = router;