// ---------------------------------------------------------------------------
// This example code was used to successfully communicate with 15 ultrasonic sensors. You can adjust
// the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
// "sonar" array. You also need to change the pins for each sensor for the NewPing objects. Each sensor
// is pinged at 33ms intervals. So, one cycle of all sensors takes 495ms (33 * 15 = 495ms). The results
// are sent to the "oneSensorCycle" function which currently just displays the distance data. Your project
// would normally process the sensor results in this function (for example, decide if a robot needs to
// turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
// to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
// processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------------------------
#include "NewPing.h"

#define SONAR_NUM     2 // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];

volatile unsigned long startTime;

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  //NewPing(12, MAX_DISTANCE), //0 // Each sensor's trigger pin, echo pin, and max distance to ping.
  //NewPing(10, MAX_DISTANCE), //1
  NewPing(2, MAX_DISTANCE), //2 
  NewPing(7, 3, MAX_DISTANCE) //Transmitter
};

void setup() {
  Serial.begin(115200);
  pingTimer = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting 
  attachInterrupt(0, echoCheck2, FALLING);
  attachInterrupt(1, echoCheck3, FALLING);
}

void loop() {

  if (millis() >= pingTimer) {         // Is it this sensor's time to ping?
    pingTimer += PING_INTERVAL;
    sonar[SONAR_NUM - 1].ping_interrupt(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    startTime = micros();
    unsigned long maxTime = sonar[SONAR_NUM - 1].get_max_time();
    sonar[SONAR_NUM - 2].ping_timer(maxTime); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    //sonar[SONAR_NUM - 3].ping_timer(maxTime); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    //sonar[SONAR_NUM - 4].ping_timer(maxTime); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    print_all();
  }
}

void echoCheck_timer() { // If ping received, set the sensor distance to array.
  if (sonar[SONAR_NUM - 2].check_timer())
  {
    cm[SONAR_NUM-2] = sonar[SONAR_NUM - 2].ping_result / US_ROUNDTRIP_CM;

  }
 
  if (sonar[SONAR_NUM - 1].check_timer())
  {
    cm[SONAR_NUM-1] = sonar[SONAR_NUM - 1].ping_result / US_ROUNDTRIP_CM;

  }
}

void echoCheck2()
{
  if (sonar[SONAR_NUM - 2].check_timer())
  {
    //cm[SONAR_NUM-2] = sonar[SONAR_NUM - 2].ping_result / US_ROUNDTRIP_CM;
    cm[SONAR_NUM-1] = (micros() - startTime) / US_ROUNDTRIP_CM;
  }
}

void echoCheck3()
{
  if (sonar[SONAR_NUM - 1].check_timer())
  {
    //cm[SONAR_NUM-1] = sonar[SONAR_NUM - 1].ping_result / US_ROUNDTRIP_CM;
    cm[SONAR_NUM-1] = (micros() - startTime) / US_ROUNDTRIP_CM;
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
