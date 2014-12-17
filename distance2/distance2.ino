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

#define SONAR_NUM     4 // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer; // Holds the times when the next ping should happen for each sensor.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(13, 12, MAX_DISTANCE), //0 // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(11, 10, MAX_DISTANCE), //1
  NewPing(9, 8, MAX_DISTANCE), //2 
  NewPing(7, 6, MAX_DISTANCE) //Transmitter
};

void setup() {
  Serial.begin(115200);
  pingTimer = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  sonar[0].ping_timer_receiver(echoCheck);
  sonar[1].ping_timer_receiver(echoCheck);
  sonar[2].ping_timer_receiver(echoCheck);
  sonar[3].ping_timer_receiver(echoCheck);
 
}

void loop() {
  //for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
  if (millis() >= pingTimer) {         // Is it this sensor's time to ping?
    pingTimer += PING_INTERVAL;
    sonar[3].ping_timer_transmitter(); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    Serial.print("sending signal");
  }
}

void echoCheck() { // If ping received, set the sensor distance to array.
  Serial.print("in echo check");
  if (sonar[currentSensor].check_timer())
  {
    unsigned int cm = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
    sonar[currentSensor].ping_timer_receiver(echoCheck);
    Serial.print(currentSensor);
    Serial.print("=");
    Serial.print("cm ");
  }
}
