int input=A0;
void setup() {
  // put your setup code here, to run once:
pinMode(input,INPUT);
Serial.begin(9600);       //setting up your serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(input)*5.0/1023);   //reading from the input pin and scaling it as the ADC has values ranging from 0-1023 and Arduino has voltage range of 0-5 hence slope is equal to 5/1023
delay(3000);
}
