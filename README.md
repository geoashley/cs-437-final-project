## Setup
Download the helper library from https://www.twilio.com/docs/node/install. 

Find your Account SID and Auth Token at twilio.com/console and set the environment variables. See http://twil.io/secure

setup a .env file with the below config

````
TWILIO_ACCOUNT_SID = <>
TWILIO_AUTH_TOKEN = <>
FROM_PHONE_NUMBER = <>
````
Start the notification app
````
node index.js
````


Sample notify request

http://localhost:3000/notify

````
{
	"temp":21,
	"vibration":100,
	"moisture":2233",
	"message":"thresholds breached"
}
````
Sample subscrible request


http://localhost:3000/subsribe

````
{
	"sendto":"+14169998888",
	"name":"ashley"
}