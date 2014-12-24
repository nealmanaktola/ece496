//Ultrasonic Sensor Test;
#include "TimerOne.h"
#include "NewPing.h"

#define SONAR_NUM 4
#define TIMER_FREQ_US 24
#define PING_INTERVAL 33 
#define MAX_DISTANCE 200


unsigned int cm;
unsigned long pingTimer;
volatile int trigger = 0;

NewPing sonar = NewPing(8,6,MAX_DISTANCE);

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
   
    sonar.ping_interrupt(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).   
    trigger = 1;

    print_all();
  }
}

void echoCheck()
{
  if (trigger && sonar.check_timer())
  {
    cm = sonar.ping_result / US_ROUNDTRIP_CM;
    trigger = 0;
  }	
}

void print_all()
{
  for (int i =0; i < SONAR_NUM; i++)
  {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("    ");   
  } 

  Serial.println();
}
