# Harviot API
[Click Here](http://api.harviot.com) to visit our API. This restful API serves as a 
## Routes
Every request starts at the root url: `http://api.harvito.com`. All methods are listed below: 
### User
Create a user

	PATH: /users 
	METHOD: POST
	CONTENT-TYPE: Application/JSON
	BODY: {email: "your@email.com", password: "password"}

Sign in

	PATH: /auth?entity=user 
	METHOD: POST
	CONTENT-TYPE: Application/JSON
	BODY: {email: "your@email.com", password: "password"}
	RESPONSE: {
		_id: "user_id",
		_role: "user_role",
		_ent: "entity"
	}

Authenticate

	PATH: /auth
	METHOD: GET
	BODY: