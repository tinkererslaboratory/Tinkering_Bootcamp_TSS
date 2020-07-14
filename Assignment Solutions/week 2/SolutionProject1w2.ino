#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h> 

const char* ssid     = "Aniket";
const char* password = "123456712";

int REDLED = 21;
int GREENLED = 32;
long ptime,currtime;
int acases,deaths,pacases,pdeaths;

void setup() 
{

  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  Serial.begin(9600);

  WiFi.enableSTA(true);
  
  delay(2000);

  connectToWifi();
  currtime = 0;
  ptime = currtime;

  initializePcases();

}

void loop(){
  currtime = millis()/1000;
  if(WiFi.status() == WL_CONNECTED){
    if(currtime - ptime >= 86400){
      ptime = currtime;
      doTheTask();
    }
  }
  else{
     Serial.println("WiFi not connected. Please Turn it on.");
     delay(1000);
     connectToWifi();
  }
}

void connectToWifi()
{

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

void initializePcases()
{
  // Here you have to initialize the pacases,pdeaths with the current value
  // you can fetch it just like that or can copy paste from the wikipedia as this is for one time only.
  HTTPClient httpa;
  HTTPClient httpd;
  httpa.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=YABAQ2FIBHP4EO03");
  httpd.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=OARUEY33LRTU5PME");
  int httpCodeA = httpa.GET();
  int httpCodeD = httpd.GET();
  if (httpCodeD > 0 && httpCodeA > 0){ // try to get the value via webpage.
   String stractiveCases = httpa.getString();
   String strdeaths = httpd.getString();
   pacases = stractiveCases.toInt();
   pdeaths = strdeaths.toInt();
  }
  else{  // if some error happens you can enter data manually.
    pacases = 244814;
    pdeaths = 19268;
  }
}

void doTheTask()
{
  // Here you have to fetch data every time of Active Cases and Deaths for Corona in India(For whole country and not state-wise)
  // Store the data in the variable defined and check whether this data is above or below 1 percent increase from previous datas
  // If any of the data is above 1 percent increase glow REDLED or else glow GREENLED
  // Also remember to turn off other LED
  // Then change previous data to current so to check again from this next day
  HTTPClient httpa;
  HTTPClient httpd;
  httpa.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=YABAQ2FIBHP4EO03");
  httpd.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=OARUEY33LRTU5PME");
  int httpCodeA = httpa.GET();
  int httpCodeD = httpd.GET();
  if (httpCodeD > 0 && httpCodeA > 0){ // take data if access is given to both the webpage
    String stractiveCases = httpa.getString();
    String strdeaths = httpd.getString();
    acases = stractiveCases.toInt();
    deaths = strdeaths.toInt();
    float perA = ((acases-pacases)*100.0)/pacases;
    float perD = ((deaths-pdeaths)*100.0)/pdeaths;
    if (perA >1 || perD>1){
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, LOW);
    }
    else{
      digitalWrite(REDLED, LOW);
      digitalWrite(GREENLED, HIGH);
    }
    pacases = Active;
    pdeaths = Deaths;
  }
  else{  // otherwise do anything to show that data is not been accessed
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
      // I turned off both the LED, you can use any method to show this case to the user.
  }
}
