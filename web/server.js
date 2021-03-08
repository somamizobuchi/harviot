if (process.env.NODE_ENV === 'development') {
	require('dotenv').config()
}
const express = require('express')
const app = express();
const server = require('http').Server(app)
const cookieParser = require('cookie-parser')
const marked = require('marked')
const fs = require('fs')
// Routers
const authRouter = require('./routers/auth').Router
const usersRouter = require('./routers/users')
const plantsRouter = require('./routers/plants')
require('./utils/mongoose')

// Initialize WebSockets
require('./utils/ws')(server)
// Parse JSON request body
app.use(express.json())
app.use(cookieParser())

// Serve README at api root path
const README = fs.readFileSync('README.md', 'utf-8')
app.get('/', (req, res) => {
	res.send(marked(README))
})

app.get('/wstest', (req, res) => {
	res.sendFile(__dirname + '/wstest.html')
})

// ROUTERS
app.use('/users', usersRouter)
app.use('/auth', authRouter)
app.use('/plants', plantsRouter)

// Start Listening
server.listen(process.env.PORT, () => {
	console.log(`Server listening on port: ${process.env.PORT}`)
})