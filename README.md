## App Setup

Find your Account SID and Auth Token at twilio.com/console and set the environment variables. See http://twil.io/secure

setup a .env file with the below config

````
TWILIO_ACCOUNT_SID = <>
TWILIO_AUTH_TOKEN = <>
FROM_PHONE_NUMBER = <>
````

Set up the notification app

````
npm install
````


Start the notification app

````
node index.js
````
## Testing

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


post http://localhost:3000/subsribe

````
{
	"sendto":"+14169998888",
	"name":"ashley"
}
````

## Arduino sketch setup

configure the sketch 
	
	1. Change the wifi/password to connect to wifi to network
	
	2. Change the server config for notification service.


````
//wifi setup
char ssid[] = "wifi-host";
char pass[] = "passcode";


char   HOST_NAME[] = "server_ip"; // hostname of web server:
````