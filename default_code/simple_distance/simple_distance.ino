int trigPin = 7;    //Trig - green Jumper
int echoPin = 6;    //Echo - yellow Jumper
long duration, cm, inches;
volatile int start = 1;
volatile int counter = 0;
volatile int num = 0;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop()
{
 
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
 
   
   Serial.print("Distance From Sensor: ");
   Serial.print(cm);
   Serial.println();
//  
//  if (cm < 60)
//  {
//    //Serial.print(cm);
//    //Serial.print(",");
//    num++;
//    if (start  == 0)
//      start = 1;    
//  }
//  else
//  {
//    if (start >= 1)
//      start++;
//    if (start == 3)
//    {
////      Serial.print(num);
////      Serial.println();
////      Serial.print("Run ");
////      Serial.print(counter);
////      Serial.print(":");
//      Serial.print("Swipe");
//      start = 0;
//      num = 0;
//      counter++;
//    }
//  }  
// 
  
  delay(200);
}
