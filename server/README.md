# Harviot API
[Click Here](http://api.harviot.com) to visit our API. This restful API serves as a 
## Routes
Every request starts at the root url: `http://api.harvito.com`. All methods are listed below: 
### User
Create a user

	PATH: /users
	POST: {email: "your@email.com", password: "password"}

Sign in

	PATH: /auth
	METHO: POST
	BODY: {email: "your@email.com", password: "password"}

Authenticate

	PATH: /auth
	METHOD: GET
	BODY: