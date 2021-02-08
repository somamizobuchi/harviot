const WebSocket = require('ws')
const cookie = require('cookie')
const { verifyToken } = require('../jwt')
const uuid = require('uuid')

module.exports = (server) => {
	// Store all client sockets
	const sockets = {}
	// Create new WebSocketServer
	const wss = new WebSocket.Server({ port: 8080 })

	server.on('upgrade', (request, socket, head) => {
		console.log(head)
	})

	wss.on('connection', async (ws, req) => {
		console.log("connected")
		const url = req.headers.host + req.url
		const wsURL = new URL(url)
		const plant_id = wsURL.searchParams.get('plant_id')
		if (req.headers.cookie) {
			try {
				var { _id } = await verifyToken(cookie.parse(req.headers.cookie).auth)
			} catch (err) {
				console.log(err)
			}
		}
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