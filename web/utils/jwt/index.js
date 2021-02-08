const jwt = require('jsonwebtoken')


exports.verifyToken = async (token) => {
	jwt.verify(token, process.env.JWT_SECRET, (err, data) => {
		if (err) return null;
		return data
	})
}

exports.signToken = async (payload) => {
	return await jwt.sign(payload, process.env.JWT_SECRET)
}
