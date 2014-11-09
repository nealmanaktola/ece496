//Neal is the best
int trigPin = 11;    //Trig - green Jumper
int echoPin = 10;   //Echo - yellow Jumper

int trigPin2 = 12;
int echoPin2 = 13;

long duration, cm, inches;
 
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
  digitalWrite(trigPin2, LOW);
  
  delayMicroseconds(5); //why?
  
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2,HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2,LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  pinMode(echoPin2,INPUT);
  
  duration = pulseIn(echoPin, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  
  // covnvert the time into a distance 
  cm2 = (duration2/2) / 29.1;

  Serial.print("Sensor 1: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.print("Sensor 2: ");
  Serial.print(cm2);
  Serial.print("cm");
  
  delay(50);
}
