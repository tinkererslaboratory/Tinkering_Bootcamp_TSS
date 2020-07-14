/*Created by Aniket Agrawal
 *Date:13/07/2020
 *Tinkering Bootcamp - Mid-term assignment solution(project 1)
 */


// In this sketch I have made a self-irrigation system. Motor will be connected to pin 21 of nodeMCU and dht11 
// sensor to pin 2.V5 and V6 will be used to display data from dht11 onto our mobile. V1 will be used to enable
// and disable to sel-irrigation system. We will also have V2 button on mobile to turn on and off the motor manually.



#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

#define DHTPIN 2          // What digital pin we're connected to

#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int motorPin = 21;
int value = 0;
int manual = 0;

BLYNK_WRITE(V1) {  //this will be used to enable and disable the self-irrigation system
  value = param.asInt();
}

BLYNK_WRITE(V2)
{
  manual = param.asInt();
  if (manual==1){
    digitalWrite(motorPin, HIGH);
  }
  else if(value == 0){
    digitalWrite(motorPin, LOW);
  }
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);

  if (value == 1) {

    if (h < 95) {
      digitalWrite(motorPin, HIGH);
    }

    if (h > 95 && manual==0) {
      digitalWrite(motorPin, LOW);
    }
  }
}

void setup()
{

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(motorPin, OUTPUT);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
