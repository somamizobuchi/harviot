const jwt = require('jsonwebtoken')


exports.verifyToken = async (token) => {
	try {
		return await jwt.verify(token, process.env.JWT_SECRET)
	} catch (err) {
		console.log(err)
		return null
	}
}

exports.signToken = async (payload) => {
	return await jwt.sign(payload, process.env.JWT_SECRET)
}
