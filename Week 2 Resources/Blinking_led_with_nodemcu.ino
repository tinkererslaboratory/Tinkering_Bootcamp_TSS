int Led = 21; // you have to use pin number written after D in your board

void setup() {
  pinMode(Led,OUTPUT); // setting up your pin in output mode
}

// loop code runs again and again and make your led blinks

void loop() {
  digitalWrite(Led,HIGH);   // turning on the led
  delay(1000);   // glows led for 1 sec
  digitalWrite(Led,LOW);   // turing off the led
  delay(1000);  //  turns off your led for one sec
}
