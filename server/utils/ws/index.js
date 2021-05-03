const WebSocket = require('ws')
const cookie = require('cookie')
const { verifyToken } = require('../jwt')
const uuid = require('uuid')

module.exports = (server) => {
	// Store all client sockets
	const sockets = {}
	// Create new WebSocketServer
	const wss = new WebSocket.Server({ server })
	// On connection
	wss.on('connection', async (ws, req) => {
		const url = `http://${req.headers.host}${req.url}`
		let wsURL = new URL(url)
		const plant_id = wsURL.searchParams.get('plant_id')
		ws.send("Connected")
		if (!plant_id){
			ws.send("You must specify a plant id. Closing connection...")	
			return ws.close()
		} 
		var _id, _ent;
		if (req.headers.cookie) {
			try {
				let token = cookie.parse(req.headers.cookie).auth;
				let data = await verifyToken(token);
				_id = data._id;
				_ent = data._ent;
			} catch (e) {
				console.log(e);
				ws.send("Error parsing cookie. Closing connection...")
				ws.close()
			}
		} else {
			_id = uuid.v4()
			_ent = 'user'
		}
		ws._id = _id
		ws._ent = _ent
		if (_id === plant_id && _ent === 'plant') {
			ws._users = {}
		} else {
			if (!ws._plants) ws._plants = {}
			if (sockets[plant_id]) {
				sockets[plant_id]._users[_id] = _id;
				ws._plants[plant_id] = plant_id;
			} else {
				ws.close()
			}
		}
		sockets[_id] = ws
		// Message sent from a scoket
		ws.on('message', message => {
			if (ws._ent === 'plant') {
				for (const user in ws._users) {
					sockets[user].send(message)
				}
			} else {
				const data = JSON.parse(message)
				const send = new Uint8Array(data.set)
				sockets[data.target].send(send, { binary: true })
			}
		})
		// Connection closed
		ws.on('close', () => {
			if (ws._ent === 'user') {
				for (const plant in ws._plants) {
					if (sockets[plant]) {
						delete sockets[plant]._users[ws._id]
					}
				}
			}
			delete sockets[ws._id]
		})
		// Error handling
		ws.on('error', err => {
			console.error(err)
		})
	})
}