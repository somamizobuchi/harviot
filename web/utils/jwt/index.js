const jwt = require('jsonwebtoken')

exports.verifyToken = (token) => {
	return jwt.verify(token, process.env.JWT_SECRET)
}

exports.signToken = async (payload) => {
	return await jwt.sign(payload, process.env.JWT_SECRET)
}
