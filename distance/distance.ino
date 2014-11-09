//Neal is the best
int trigPin = 12;    //Trig - green Jumper
int echoPin = 11;    //Echo - yellow Jumper

int trigPin2 = 9;
int echoPin2 = 8;
long duration, duration2, cm, cm2, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5); //why?
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
  
  delay(50);
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5); //why?
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
 
  // convert the time into a distance
  cm2 = (duration2/2) / 29.1;
  
   
  Serial.print("Sensor 1: ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.print("Sensor 2: ");
  Serial.print(cm2);
  Serial.print(" cm");  
  
  Serial.println();
  
  
}
