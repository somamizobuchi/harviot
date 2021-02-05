if (process.env.NODE_ENV === 'development') {
	require('dotenv').config()
}
const express = require('express')
const app = express();
const server = require('http').Server(app)
const authRouter = require('./routers/auth');

// Initialize WebSockets
require('./utils/ws')(server)
// Parse JSON request body
app.use(express.json())

app.get('/', (req, res) => {
	res.send("<h1>Welcome!</h1>");
})

app.use('/auth', authRouter)

server.listen(process.env.PORT, () => {
	console.log(`Server listening on port: ${process.env.PORT}`)
})