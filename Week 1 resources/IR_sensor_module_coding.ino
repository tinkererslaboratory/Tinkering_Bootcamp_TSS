int irObstaclePin = 2;   // This is our input pin
int Obstacle = HIGH;     // HIGH MEANS NO OBSTACLE
void setup() 
{
 pinMode(irObstaclePin, INPUT);   // Initializing Input pin
 Serial.begin(9600);       // Initializing serial monitor
}
void loop() 
{
 Obstacle = digitalRead(irObstaclePin);  //This reads the input
 if (Obstacle == LOW)
 {
   // If the input is low it means there is an obstacle
   Serial.println("OBSTACLE!!, OBSTACLE!!");  
 }
 else
 {
   // else there is no obstacle
   Serial.println("clear");
 }
 delay(200); 
}
