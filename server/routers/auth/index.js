const router = require('express').Router()
const { signToken, verifyToken } = require('../../utils/jwt')
const bcrypt = require("bcrypt")
const User = require('../../models/User')
const Plant = require('../../models/Plant')

// Roles
ROLES = { basic: 'basic', admin: 'admin' }

// Cookie-based auth middleware
const auth = async (req, res, next) => {
	// Verify Token
	if (!req.cookies['auth']) return res.sendStatus(403)
	var data = await verifyToken(req.cookies['auth'])
	if (!data) return res.sendStatus(403)
	res.locals._id = data._id
	res.locals._role = data._role
	res.locals._ent = data._ent
	return next()
}

// Role verification middleware
const verifyRole = (role) => {
	return (req, res, next) => {
		if (res.locals._role === role) return next()
		return res.sendStatus(403)
	}
}

// Authenticate User
router.get('/', auth, (req, res) => {
	return res.status(200).json({ _id: res.locals._id })
})

// User Login
router.post('/', async (req, res) => {
	// Check for entity query
	const { entity } = req.query
	if (!entity) return res.sendStatus(422)
	// extract from query body
	const { _id, email, password } = req.body
	// Input validation
	if ((_id && email) || (!_id && !email) || !password) {
		return res.sendStatus(422)
	}

	// Database query
	let doc
	try {
		switch (entity) {
			case 'user':
				doc = await User.findOne({ email })
				break
			case 'plant':
				doc = await Plant.findById(_id)
				break
			default:
				return res.sendStatus(422)
		}
	} catch (e) {
		console.log(e)
		return res.sendStatus(500)
	}
	// user doesn't exist
	if (!doc) return res.sendStatus(403)
	// Compare passwords
	try {
		let match = await bcrypt.compare(password, doc.password)
		if (!match) return res.sendStatus(401)
		// sign cookie
		let payload = {
			_id: doc._id,
			_role: doc._role,
			_ent: entity
		}
		let token = await signToken(payload)
		return res.cookie('auth', token).status(200).json({
			firstname: doc.firstname,
			lastname: doc.lastname,
			email: doc.email
		})
	} catch (e) {
		console.log(e)
		return res.sendStatus(500)
	}
})

// Logout
router.delete('/', (req, res) => {
	return res.clearCookie('auth').sendStatus(200)
})


module.exports = {
	auth: auth,
	verifyRole: verifyRole,
	Router: router,
	ROLES: ROLES
}