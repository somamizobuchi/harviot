const router = require('express').Router()
const { signToken, verifyToken } = require('../../utils/jwt')
const User = require('../../models/User')
const Plant = require('../../models/Plant')

// Roles
ROLES = { basic: 'basic', admin: 'admin' }

// Cookie-based auth middleware
const auth = async (req, res, next) => {
	// Verify Token
	var data = await verifyToken(req.cookies['auth'])
	if (!data) return res.sendStatus(403)
	console.log(data)
	res.locals._id = data._id
	res.locals._role = data._role
	return next()
}

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
	const { entity } = req.query
	if (!entity) return res.sendStatus(422)
	// extract from query body
	const { _id, email, password } = req.body
	// Input validation
	if ((_id && email) || (!_id && !email) || !password) {
		return res.sendStatus(422)
	}

	var doc;
	switch (entity) {
		case 'user':
			try {
				doc = await User.login(email, password)
			} catch (err) {
				console.log(err)
				return res.sendStatus(500)
			}
			break;
		case 'plant':
			try {
				doc = await Plant.login(_id, password)
			} catch (err) {
				console.log(err)
				return res.sendStatus(500)
			}
			break;
		default:
			return res.sendStatus(422)
	}

	// Sign Token
	var token = await signToken({
		_id: doc._id,
		_role: doc._role | null,
		_ent: entity
	})
	// set cookie
	return res.cookie('auth', token).sendStatus(200)
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