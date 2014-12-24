//Ultrasonic Sensor Test;
#include "TimerOne.h"
#include "NewPing.h"

#define SONAR_NUM 4
#define TIMER_FREQ_US 24
#define PING_INTERVAL 33 

volatile int waiting_responses[SONAR_NUM];
volatile int response_count = SONAR_NUM;

volatile int cm[SONAR_NUM];

unsigned long pingTimer;

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(12, MAX_DISTANCE), //0 // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(10, MAX_DISTANCE), //1
  NewPing(2, MAX_DISTANCE), //2 
  NewPing(7, 3, MAX_DISTANCE) //Transmitter
};

void setup()
{
	Serial.begin(9600);

	pingTimer = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting 

	Timer1.initialize(TIMER_FREQ_US); 
	Timer1.attachInterrupt(echoCheck);
}

void loop() {
  if (millis() >= pingTimer) {         // Is it this sensor's time to ping?
    
    for (i = 0; i < SONAR_NUM; i++)
    {
      waiting_responses[i] = 1;
    }
    
    response_count = SONAR_NUM;

    Timer1.restart();

    pingTimer += PING_INTERVAL;
   	
    //Transmitter Ping
    sonar[SONAR_NUM - 1].ping_interrupt(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).   
    unsigned long maxTime = sonar[SONAR_NUM - 1].get_max_time();   

    int i;

    //Receiver Responses    
    for (i = 0; i < (SONAR_NUM -1); i++)
    {
        sonar[i].ping_timer(maxTime);
    }    

    print_all();
  }
  //All Sensors have received echo's or timed_out, stop timer interrupts
  if (response_count == 0)
  {
  	Timer1.stop();
  }
}

void echoCheck()
{
  for (i = 0; i < SONAR_NUM; i++)
  {
    if (waiting_responses[i] && sonar[i].check_timer())
    {
      waiting_responses[i] = 0;
      response_count--;
      cm[i] = sonar[i].ping_result / US_ROUNDTRIP_CM;
    }	
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
