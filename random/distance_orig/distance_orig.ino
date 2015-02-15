//source
int trigPin3 = 7;

//Neal is the best
int trigPin = 13;    //Trig - green Jumper
int echoPin = 12;

int echoPin3 = 6;

int trigPin1 = 11;    //Trig - green Jumper
int echoPin1 = 10;

int trigPin2 = 9;    //Trig - green Jumper
int echoPin2 = 8;

long duration, cm, inches;
long duration1, cm1, inches1;
long duration2, cm2, inches2;
long duration3, cm3, inches3;


void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT); 
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  
  /*pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);*/
}


 
void loop()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  
  delayMicroseconds(5); //why?
  
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin1,HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3,HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);

 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  //pinMode(echoPin2,INPUT);
  
  duration = pulseIn(echoPin, HIGH);
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);    
//  duration2 = pulseIn(echoPin2, HIGH);
  
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  cm1 = (duration1/2) / 29.1;
  cm2 = (duration2/2) / 29.1;
  cm3 = (duration3/2) / 29.1;
  // covnvert the time into a distance 
//  cm2 = (duration2/2) / 29.1;

  Serial.print("Sensor 0: ");
  Serial.print(cm);
  Serial.print("cm");
  
  Serial.print("Sensor 1: ");
  Serial.print(cm1);
  Serial.print("cm");
  
  Serial.print("Sensor 2: ");
  Serial.print(cm2);
  Serial.print("cm");
  
  Serial.print("Sensor 3: ");
  Serial.print(cm3);
  Serial.print("cm");

  Serial.println();
  
  delay(50);
}

