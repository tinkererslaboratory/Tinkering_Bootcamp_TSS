int buzzPin = 12;   // This is our output pin
void setup() 
{
 pinMode(buzzPin, OUTPUT);   // Initializing output pin
}
void loop() 
{
 digitalWrite(buzzPin, LOW); // Beeping ON
 delay(1000);
 digitalWrite(buzzPin, HIGH); // Beeping OFF
 delay(1000);
}
