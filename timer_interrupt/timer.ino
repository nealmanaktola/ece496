//Program should print consecutive numbers every second until it reaches 30.
#include "TimerOne.h"


#define TIMER_FREQ_US 1000000

volatile int x = 0;
int y = 0;



void setup()
{
	Serial.begin(9600);
	Timer1.initialize(TIMER_FREQ_US); //1 second interrupt
	Timer1.attachInterrupt(echoCheck);
}

void loop()
{
	if (y != x)
	{
		Serial.print(x)
		Serial.println();
		y = x;
	}
	if (x == 30)
	{
		Timer1.stop();
	}
}

void echoCheck()
{
	x++;
}