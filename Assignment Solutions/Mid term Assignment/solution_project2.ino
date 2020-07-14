/*Created by Aniket Agrawal
 *Date:13/07/2020
 *Tinkering Bootcamp - Mid-term assignment solution(project 2)
 */
 
// Both Project 1 and 2 are similar almost. so i haven't added comments in this.

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int IR=3;
int motor=21;
int manual=0;
int command=0;
BlynkTimer timer;


char auth[] = "mSrQPGjXOj5vUiZP9C_yuBs69agKauBT";

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void setup()
{
  pinMode(IR,INPUT);
  pinMode(motor,OUTPUT);
  
  Serial.begin(9600);

  timer.setInterval(500l,self_sanitizer);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)
{
  manual=param.asInt();
}

BLYNK_WRITE(V2)
{
  command=param.asInt();
}

void self_sanitizer()
{
  if(manual==0){ 
    int sensorReading=digitalRead(IR);
    if(sensorReading=HIGH){
      digitalWrite(motor,HIGH);
    }
    else{ 
      digitalWrite(motor,LOW);
    }
  }
  else{ 
    digitalWrite(motor,command);
  }
}
