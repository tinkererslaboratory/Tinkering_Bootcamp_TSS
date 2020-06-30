#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HTTPClient.h> 
// these are the libraries used

WebServer server ( 80 );  // creating a variable for our webserver

const char* ssid     = "Aniket";   // wifi name
const char* password = "123456712"; // wifi password

int LEDPIN = 21;   // led pin number


void setup() 
{

  pinMode(LEDPIN, OUTPUT);     // setting led as output
  digitalWrite(LEDPIN, LOW);   // initializing led as low
  Serial.begin(9600);   // setting up serial monitor


  connectToWifi();

}

void connectToWifi()
{
  WiFi.enableSTA(true);   // enabling wifi port
  
  delay(2000);

  WiFi.begin(ssid, password);   // connnecting to wifi
  
  while (WiFi.status() != WL_CONNECTED) { 
        delay(500);
        Serial.print(".");   // printing "." till wifi is not connected
    }
  Serial.println("");
  Serial.println("WiFi connected");   
  Serial.println("IP address: ");  
  Serial.println(WiFi.localIP());  // wifi connected and printing it's IP address
}



void loop(){
  if(WiFi.status() == WL_CONNECTED){
     digitalWrite(LEDPIN, HIGH);  // glowing the led if wifi is connected
     HTTPClient http;   // making a variable for interacting to any webpage
     http.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=T9IX646NPLSLF9QK");  // connecting with this webpage
     int httpCode = http.GET();
     if(httpCode>0){ // condition written is if connected
      String confirmedCases = http.getString();   // storing confirmed cases
      confirmedCases = confirmedCases.substring(4,10);  // triming it
      Serial.print("Confirmed Cases in Bihar - ");
      Serial.println(confirmedCases); // printing on serial monitor
     }
  }
  else{ /// if wifi gets disconnected the whole  wifi will be again connected by the same process
     digitalWrite(LEDPIN, LOW);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
     }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
