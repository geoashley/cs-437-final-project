#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

//wifi setup
char ssid[] = "wifi-host";
char pass[] = "passcode";
WiFiClient wifi;
int status = WL_IDLE_STATUS;

//http call setup
int    HTTP_PORT   = 3000;//app port
String HTTP_METHOD = "POST";
char   HOST_NAME[] = "server_ip"; // hostname of web server:
String PATH   = "/notify";
String contentType = "application/json";

//sensor pins
int tempsensorPin = A0;
int vibrationPin = A2;
int moistsensorPin = A1;

// sensor threshold value
float tempThreshold = 25.0;
int moistureThreshold = 500;
int vibThreshold = 20;

int count =0;
void setup() {
  pinMode(moistsensorPin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(tempsensorPin, INPUT);
  Serial.begin(9600);
  
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  Serial.println("Connected to the WiFi network");
}

void loop() {
  // main code here, to run repeatedly:
  int tempreading = analogRead(tempsensorPin);
  int soilSensorValue = analogRead(moistsensorPin);
  int vibrationValue = analogRead(vibrationPin);
  float temperatureC = 0.48828125* tempreading;
  

  // Print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperatureC);

  Serial.print(" Vibration: ");
  Serial.print(vibrationValue, DEC);
  
  Serial.print(" Soil Moisture: ");
  Serial.println(soilSensorValue);
  
  if ((soilSensorValue < moistureThreshold) && (temperatureC < tempThreshold) && (vibrationValue >vibThreshold)){
    Serial.println(" - earth quake!! - Sending notification!!");

    // Prepare JSON document
    DynamicJsonDocument doc(2048);
    doc["temp"] = temperatureC;
    doc["vibration"] = vibrationValue;
    doc["moisture"] = soilSensorValue;
    doc["message"] = "Earthquake threasholds breached" ;
    
    // Serialize JSON document
    String json;
    serializeJson(doc, json);

    // send the POST request
    Serial.print("json: ");
    Serial.println(json);
    HttpClient client = HttpClient(wifi, HOST_NAME, HTTP_PORT);
    client.post(PATH, contentType, json);

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
  
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
  }
  
  delay(500);

}


