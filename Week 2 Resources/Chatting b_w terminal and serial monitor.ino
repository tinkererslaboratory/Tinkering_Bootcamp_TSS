#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <analogWrite.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "C2ZNCPRpY58xr0gfXH5JpWOwLGQTKV1Q";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Aniket";
char pass[] = "123456712";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);  // Starting connection
}

void loop()
{
  Blynk.run();  // allowing blynk to run continously
}

BLYNK_WRITE(V2)
{
  String coming = param.asStr();   // taking the data from terminal
  Serial.println(coming);    // printing it on serial monitor
  String going = Serial.readString();  // taking the data from serial monitor
  while(going==""){
    going = Serial.readString();   // taking the data until it is not empty
  }
  Blynk.virtualWrite(V2,going);   // printing that data into terminal
}
