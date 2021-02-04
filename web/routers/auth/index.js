const router = require('express').Router()
const { signToken } = require('../../utils/jwt')

router.post('/login', async (req, res) => {
	const { email, password } = req.body
	if (!email | !password) {
		console.log("not all details provided")
		return res.status(403)
	}
	// Implement User Login
	const token = await signToken({
		user: email
	})
	res.cookie('auth', token).status(200).json(token)

})

module.exports = router;