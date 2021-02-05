const WebSocket = require('ws')
const cookie = require('cookie')
const { verifyToken } = require('../jwt')
const uuid = require('uuid')


module.exports = (server) => {
	// Store all client sockets
	const sockets = {}
	// Create new WebSocketServer
	const wss = new WebSocket.Server({ server: server })

	wss.on('connection', async (ws, req) => {
		const { _id } = await verifyToken(cookie.parse(req.headers.cookie).auth)
		// If invalid cookie
		if (!_id) _id = uuid.v4()
		sockets[_id] = ws
		ws.on('message', message => {
			console.log(JSON.parse(message))
		})
		ws.on('close', () => {
			console.log("Disconnected")
			delete sockets[_id]
		})
	})
}