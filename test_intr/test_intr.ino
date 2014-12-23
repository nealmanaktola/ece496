/*  Ultrasonic Ranging Transducer
 *
 *  Version 0.1 Revision 1 November 2011
 *
 *  Description:
 *    Initiates an ultrasonic ping and waits for a response via interrupt,
 *    calculates the range to an object/body of water
 *    Sensor should be able to detect up to 3m
 *    Sensor is HC-SR04
 */

/* Defines */
#define TIMER_US_PER_TICK 4 // 16MHz / 64 cycles per tick
#define TIMER_OVERFLOW_US TIMER_US_PER_TICK * 65536 // timer1 is 16bit
#define CM_PER_SEC 34030    // Speed of sound

/* Pin Assignments */
const int USOUND_TRIGGER = 7;  // The TRIG pin is connected to pin7
const int USOUND_ECHO = 3;     // The ECHO pin is connected to pin3 (which is also INT1)

/* Globals  - need to use volatile as they are modifying values within interrupt routines */
volatile long oflow_start = -1;  // indicates number of overlows when we started timing
volatile long timer1_start = 0;  // value of timer when we start timing
volatile long echo_time = -1;    // time of last/current echo
volatile int timer1_oflow = 0;  // number of times that timer1 has overflowed

/* Interrupt Routines */
void echo_response() {
  // Only grab the time difference if we have triggered the pulse (ie the oflow_start is > 0)
  if (oflow_start != -1)
    echo_time = time_difference();
}

// Increment timer1_flow value every time timer1 overflows so we can count the number of 209.7mS's to add)
ISR(SIG_OVERFLOW1) {
  timer1_oflow += 1;
};

/* Function to return the time difference */
long time_difference() {
  long us;
  us = (timer1_oflow - oflow_start) * 65536;  // overflows every 65k ticks, so nbr of overflows*65k
  us += (TCNT1 - timer1_start);               // and add the timer remainder
  us *= TIMER_US_PER_TICK;                    // convert it to microseconds
  return us;
}

/* Function to trigger a pulse and start timing */
void trigger_pulse() {
  echo_time = -1;      // clear any current time
  oflow_start = -1;    // ignore INT1 for now

  digitalWrite(USOUND_TRIGGER, LOW);      // Send 2ms LOW pulse to ensure we get a nice clean pulse
  delayMicroseconds(2);

  digitalWrite(USOUND_TRIGGER, HIGH);    // Ping is triggered by a HIGH pulse of 2 or more microseconds
  delayMicroseconds(10);
  digitalWrite(USOUND_TRIGGER, LOW);      // End the ping

  timer1_start = TCNT1;                    // Get the current time
  oflow_start = timer1_oflow;
}

/* Function to convert echo_time to a distance value */
void print_echo_distance() {
  long cm;

  // Divide echo_time by 1000000 in three steps for efficiency
  cm = ((echo_time/100) * (CM_PER_SEC/100))/100;
  cm /= 2;  // divide by 2 for one way (not the return trip)
  Serial.print("uS = ");
  Serial.print(echo_time);
  Serial.print("\tcm = ");
  Serial.print(cm);
  Serial.print("\n");
  Serial.flush();
}

/* Setup */
void setup() {
  Serial.begin(9600);      // Start serial port comms

  pinMode(USOUND_TRIGGER, OUTPUT);    // Set trigger pin as output
  pinMode(USOUND_ECHO, INPUT);        // Set echo pin as input

  // Attach interrupt to INT1 (pin 3)
  attachInterrupt(1, echo_response, FALLING);      // return pulse is detected when the echo pulse drops to LOW

  TCNT1 = 0;              // Start timer 1
  TCCR1A = 0x00;          // Disconnect OC1 from timer/counter, disable PWM
  TCCR1B = 0x03;          // timer prescaper = clock/64, increments every 3.2us, overflows every 209.7mS
  TIMSK1 |= _BV(0);       // enable timer1 overflow interrupt

  sei();                 // enable global interrupts
}

/* Main Loop */
void loop () {
  trigger_pulse();  // trigger a pulse and start the timer
  Serial.println("Pulse triggered!");

  // Wait until a return pulse is received
  while (echo_time == -1) { }
  print_echo_distance();  // convert to a distance
  delay(1000);            // wait 1 seconds between pulses
}
