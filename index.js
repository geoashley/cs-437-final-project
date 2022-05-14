const express = require('express')
const app = express()
const port = 3000

const dotenv = require('dotenv');
dotenv.config();

// Type 2: Persistent datastore with manual loading
var Datastore = require('nedb')
  , db = new Datastore({ filename: './nofiy.db' });
db.loadDatabase(function (err) {    // Callback is optional
  // Now commands will be executed
});


var bodyParser = require('body-parser')
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
})); 

const accountSid = process.env.TWILIO_ACCOUNT_SID;
const authToken = process.env.TWILIO_AUTH_TOKEN;
const client = require('twilio')(accountSid, authToken); 


app.post('/subsribe', (req, res) => {
   
  const sendTo = req.body.sendto
  const name = req.body.name
  var doc = { name: name
  , sendTo: sendTo
  };

  db.insert(doc, function (err, newDoc) {   
    console.log(newDoc)
  });
  res.send('Saved Subscription') 
})

app.post('/notify', (req, res) => {
   
  const temp = req.body.temp
  const moisture = req.body.moisture
  const vibration = req.body.vibration
  const message = req.body.message

  const smsBody  = message + ` -> temp ${temp} , vibration ${vibration}, soil moisture ${moisture} ` 

  // Find all documents in the collection
  db.find({}, function (err, docs) {
    docs.forEach(subscriber => {
      const smsMessage = `Hello ${subscriber.name}, `+ smsBody
      client.messages
      .create({
          body: smsMessage,
          from: process.env.FROM_PHONE_NUMBER,
          to: subscriber.sendTo
      })
      .then(message => console.log(message.sid));
    })
  });

  res.send('Send all notification')  
})

app.listen(port, () => {
  console.log(`Nofication app listening on port ${port}`)
})