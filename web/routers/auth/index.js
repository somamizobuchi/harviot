const router = require('express').Router()
const bcrypt = require('bcrypt')
const { signToken, verifyToken } = require('../../utils/jwt')
const User = require('../../models/User')

// Cookie-based auth middleware
const auth = async (req, res, next) => {
	// Verify Token
	try {
		var data = await verifyToken(req.cookies['auth'])
	} catch (err) {
		return res.sendStatus(403)
	}
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
		return res.status(403)
	}
	// Find User
	try {
		var user = await User.findOne({ email: email }, '_id').exec()
	} catch (err) {
		return res.sendStatus(500)
	}
	// User does not exist
	if (!user) return res.sendStatus(404)
	// Match passwords
	if (!(await bcrypt.compare(password, user.password))) return res.sendStatus(401)
	// Sign Token
	const token = await signToken({
		_id: user._id
	})
	// Set Cookie
	res.cookie('auth', token).sendStatus(200)
})

// Logout
router.delete('/', (req, res) => {
	return res.clearCookie('auth').sendStatus(200)
})

module.exports = router;