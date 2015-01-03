//Ultrasonic Sensor Test;
#include "TimerOne.h"
#include "NewPing.h"

#define SONAR_NUM 4
#define TIMER_FREQ_US 37
#define PING_INTERVAL 33 
#define MAX_DISTANCE 200

#define ELEMENTS 10
unsigned int cm1[ELEMENTS];
unsigned int cm2[ELEMENTS];
unsigned int cm3[ELEMENTS];
unsigned int cm4[ELEMENTS];

//element counter
unsigned int element = 0;

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
  if (cm2[element] < 70 || cm3[element] < 70 || cm4[element] < 70)
  {
    detect = 1;
  }
  else if (cm2[element] >= 70 && cm3[element] >= 70 && cm4[element] >= 70)
  {
    if (detect == 1)
    {
      Serial.println();
      Serial.print("Run: ");
      Serial.print(runNum);
      Serial.println();
      runNum ++;
    }
    detect = 0; 
  }
}
void echoCheck()
{
  if (trigger1 && sonar1.check_timer())
  {
    cm1[element] = sonar1.ping_result / US_ROUNDTRIP_CM;
    trigger1 = 0;
  }
  if (trigger2 && sonar2.check_timer())
  {
    cm2[element] = sonar2.ping_result / US_ROUNDTRIP_CM;
    trigger2 = 0;
  }	
  if (trigger3 && sonar3.check_timer())
  {
    cm3[element] = sonar3.ping_result / US_ROUNDTRIP_CM;
    trigger3 = 0;
  }
  if (trigger4 && sonar4.check_timer())
  {
    cm4[element] = sonar4.ping_result / US_ROUNDTRIP_CM;
    trigger4 = 0;
  }	
}

void print_all()
{

//    Serial.print("1");
//    Serial.print("=");
//    Serial.print(cm1[element]);
//    Serial.print("    "); 
// 
  if (detect == 1)
  {
    if (cm2[element] < 70)
    {
      Serial.print("2");
      Serial.print("=");
      Serial.print(cm2[element]);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    
    if (cm3[element] < 70)
    {
      Serial.print("3");
      Serial.print("=");
      Serial.print(cm3[element]);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    
    if (cm4[element] < 70)
    {
      Serial.print("4");
      Serial.print("=");
      Serial.print(cm4[element]);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    Serial.println();
  }
  
}
