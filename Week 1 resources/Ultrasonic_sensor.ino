int trigpin=10;
int echopin=9;
int traveltime;
void setup() {
  // put your setup code here, to run once:
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigpin,LOW);
delayMicroseconds(10);
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
traveltime=pulseIn(echopin,HIGH);  //measure the time in microseconds for the time interval for which the echopin was high.
Serial.println(traveltime*0.0165); //converting the microseconds into seconds, hence a factor of 10^-6 came and converting distance from m into cm hence we need to multiply 10^2 and dividing by 2 as the waves have travelled twice the distance.
delay(1000);                      //taking speed of sound to be 330m/s.
}
