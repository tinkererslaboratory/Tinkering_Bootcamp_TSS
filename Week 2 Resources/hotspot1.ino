#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Esp32WifiManager.h>
// libraries used


// this is the webpage we are going to create
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang=en-EN><head><meta http-equiv='refresh' content='60'/>
<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
<body>
 
<h2>Tinkerers' Laboratory<h2>
<h3>Webpage Esp32</h3>
 
<form action="/action_page">
  <ul><li>LED

  <INPUT type='radio' name='LED' value='1'>ON
  <INPUT type='radio' name='LED' value='0'>OFF</li></ul>
  <input type="submit" value="Submit">
</form> 
 
</body>
</html>
)=====";

// form action is the action taken place when any action is given by user


int LEDPIN = 21;   // led pin number
WebServer server(80);  // creating a variable for our webserver


// handleroot initializes the webpage
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}


// handleform handles the action by the user
void handleForm() {
  String LEDValue;
  LEDValue = server.arg("LED"); // value given by user on selecting the radio button
  Serial.println("Set GPIO "); 
  Serial.println(LEDValue);
  
  if ( LEDValue == "1" ) {
    digitalWrite(LEDPIN, HIGH); // if value is 1 turn on the led
    String s = MAIN_page;  // again setting the webpage
    server.send ( 200, "text/html", s );
  }
  else if( LEDValue == "0" ) 
  {
    digitalWrite(LEDPIN, LOW); // if value is 0 turn off the led
    String s = MAIN_page;  // again setting the webpage
    server.send ( 200, "text/html", s );
  } else 
  {
    Serial.println("Error Led Value");  // in any other case if some error happened
  }
}

void setup(void){
  Serial.begin(9600);  // setting up serial monitor
  pinMode(LEDPIN, OUTPUT);   // setting led as output
  digitalWrite(LEDPIN, LOW);   // initializing led as low
 
  Serial.println("Setting WiFi .... ");
  boolean result = WiFi.softAP("ESP32", "12345678");   // creating a wifi
  if(result == true)
  {
    Serial.println("Ready");  // if wifi is created
  }
  else
  {
    Serial.println("Failed!");  // if wifi is not created
  }
 
  server.on("/", handleRoot);    // initializes handleRoot() function
  server.on("/action_page", handleForm);  // initalizes handleForm() function
 
  server.begin();   // starting the server
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();   // giving the server access to handle the user
}
