//Ultrasonic Sensor Test;
#include "TimerOne.h"
#include "NewPing.h"

#define SONAR_NUM 4
#define TIMER_FREQ_US 37
#define PING_INTERVAL 40 
#define MAX_DISTANCE 200


unsigned int cm1;
unsigned int cm2;
unsigned int cm3;
unsigned int cm4;

unsigned int detect = 0;
unsigned int runNum = 1;

unsigned long pingTimer;

volatile int trigger1 = 0;
volatile int trigger2 = 0;
volatile int trigger3 = 0;
volatile int trigger4 = 0;

NewPing sonar1 = NewPing(7,6,MAX_DISTANCE);
NewPing sonar2 = NewPing(8,MAX_DISTANCE);
NewPing sonar3 = NewPing(9,MAX_DISTANCE);
NewPing sonar4 = NewPing(10,MAX_DISTANCE);

void setup()
{
	Serial.begin(9600);

	pingTimer = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting 

	Timer1.initialize(TIMER_FREQ_US); 
	Timer1.attachInterrupt(echoCheck);
}

void loop() {
  int i;
  if (millis() >= pingTimer) {         // Is it this sensor's time to ping?

    pingTimer += PING_INTERVAL;
   
    sonar1.ping_interrupt(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).   
    sonar2.ping_timer(sonar1.get_max_time());
    sonar3.ping_timer(sonar1.get_max_time());
    sonar4.ping_timer(sonar1.get_max_time());
    
    trigger1 = 1;
    trigger2 = 1;
    trigger3 = 1;
    trigger4 = 1;
    
    checkDetect();
    print_all();
  }
}

void checkDetect()
{
  if (cm2 < 70 || cm3 < 70 || cm4 < 70)
  {
    detect=3; // setting how many times nothing is accepted
  }
  else if (cm2 >= 70 && cm3 >= 70 && cm4 >= 70)
  {
    if (detect == 1)
    {
      Serial.println();
      Serial.print("Run: ");
      Serial.print(runNum);
      Serial.println();
      runNum ++;
      detect = 0;
      
    }
    else if (detect==2)
    {
       detect--; 
    }
    else if (detect==3)
    {
       detect--; 
    }

  }
}
void echoCheck()
{
  if (trigger1 && sonar1.check_timer())
  {
    cm1 = sonar1.ping_result / US_ROUNDTRIP_CM;
    trigger1 = 0;
  }
  if (trigger2 && sonar2.check_timer())
  {
    cm2 = sonar2.ping_result / US_ROUNDTRIP_CM;
    trigger2 = 0;
  }	
  if (trigger3 && sonar3.check_timer())
  {
    cm3 = sonar3.ping_result / US_ROUNDTRIP_CM;
    trigger3 = 0;
  }
  if (trigger4 && sonar4.check_timer())
  {
    cm4 = sonar4.ping_result / US_ROUNDTRIP_CM;
    trigger4 = 0;
  }	
}

void print_all()
{

  if (detect > 0)
  {
    if (cm1 < 70)
    {
    Serial.print("1");
    Serial.print("=");
    Serial.print(cm1);
    Serial.print("    "); 
    }
  
    else
    {
      Serial.print("        ");
    }
  }
 
  if (detect > 0)
  {
    if (cm2 < 70)
    {
      Serial.print("2");
      Serial.print("=");
      Serial.print(cm2);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    
    if (cm3 < 70)
    {
      Serial.print("3");
      Serial.print("=");
      Serial.print(cm3);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    
    if (cm4 < 70)
    {
      Serial.print("4");
      Serial.print("=");
      Serial.print(cm4);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    Serial.println();
  }
  
}
