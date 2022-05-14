## Setup
Download the helper library from https://www.twilio.com/docs/node/install. 
Find your Account SID and Auth Token at twilio.com/console and set the environment variables. See http://twil.io/secure

````
TWILIO_ACCOUNT_SID = <>
TWILIO_AUTH_TOKEN = <>
FROM_PHONE_NUMBER = <>
````
Start the notification app
````
node index.js
````


Sample request

http://localhost:3000/notify

````
{
	"sendto":"+4169998888",
	"message":"How are you"
}
````