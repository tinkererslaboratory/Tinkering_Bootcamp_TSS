/*Created by Aniket Agrawal
 *Date:13/07/2020
 *Tinkering Bootcamp - Mid-term assignment solution(project 3)
 */

#define BLYNK_PRINT Serial

//defining pins for input and output
#define map_display_pin V5        //display for the value of lat and long
#define map_pin V1                //map widget virtual pin
#define speed_display_pin V6      //display/gauge for the speed
#define RXPIN  21
#define TXPIN 19

#include <stdlib.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

//Create an instance of gps and serial monitor ro get values from gps tracker
TinyGPS gps;
SoftwareSerial ss(RXPIN, TXPIN);

//Blynk auth token and wifi name and password, change to actual values
BlynkTimer timer;
char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void setup() {
  // to check any errors
  Serial.begin(115200);
  //start the input from gps module
  ss.begin(4800);
  //start the Blynk connection
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getgpsData);
}


void loop() {
  Blynk.run();
  timer.run();
}

void getgpsData()
{
  bool newData = false;
  float flat, flon;
  unsigned long fix_age,fspeed;
  unsigned long chars;
  unsigned short sentences, failed;

  //get data from the gps module...Also introduces a delay of 1 second
  for(unsigned long start = millis();millis()-start<=1000;) {
    while(ss.available())
    {
      char c = ss.read();
      if(gps.encode(c))
        newData = true;
    }
  }

  //if you get some data, extract lat,long and speed from it
  if(newData)
  {    
    gps.f_get_position(&flat, &flon, &fix_age);
    fspeed = gps.f_speed_mps();

    flat = (flat == TinyGPS::GPS_INVALID_F_ANGLE) ? 0.0 : flat;
    flon = (flon == TinyGPS::GPS_INVALID_F_ANGLE) ? 0.0 : flon;
    fspeed = (fspeed == TinyGPS::GPS_INVALID_F_SPEED)?0.0 : fspeed;
  }
  //used to check for errors
  gps.stats(&chars, &sentences, &failed);
  
  if (chars == 0)
  {
    Serial.println("** No characters received from GPS: check wiring **");
    Blynk.virtualWrite(map_display_pin, "No characters received from GPS: check wiring");
    Blynk.virtualWrite(speed_display_pin, "No characters received from GPS: check wiring");
  }
  else { 
    //write the values to the corresponding pins
    Blynk.virtualWrite(map_display_pin, "The current Cordinates are: ");
    Blynk.virtualWrite(map_display_pin, flat);
    Blynk.virtualWrite(map_display_pin, flon);
    Blynk.virtualWrite(speed_display_pin, fspeed);
    Blynk.virtualWrite(map_pin, 1, flat, flon, "value");
  }
}
