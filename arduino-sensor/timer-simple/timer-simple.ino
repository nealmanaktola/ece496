//Ultrasonic Sensor Test;
#include "TimerOne.h"
#include "NewPing.h"
#include <string>
#include <sstream.h>
#define SONAR_NUM 5
#define TIMER_FREQ_US 37
#define PING_INTERVAL  33
#define MAX_DISTANCE 200
#define ALLOWED_DISTANCE 90
#define ARRAY_LENGTH 30

short cm1;
short cm2;
short cm3;
short cm4;
short cm5;
short cm2_array[ARRAY_LENGTH];
short cm3_array[ARRAY_LENGTH];
short cm4_array[ARRAY_LENGTH];
short cm5_array[ARRAY_LENGTH];

short counter = 0;

short detect = 0;
short runNum = 1;

unsigned long pingTimer;


short trigger2 = 1;
short trigger3 = 1;
short trigger4 = 1;
short trigger5 = 1;

NewPing sonar1 = NewPing(7,6,MAX_DISTANCE);
NewPing sonar2 = NewPing(8,MAX_DISTANCE);
NewPing sonar3 = NewPing(9,MAX_DISTANCE);
NewPing sonar4 = NewPing(10,MAX_DISTANCE);
NewPing sonar5 = NewPing(11,MAX_DISTANCE);

void setup()
{
	Serial.begin(9600);

	pingTimer = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting 

	Timer1.initialize(TIMER_FREQ_US); 
	Timer1.attachInterrupt(echoCheck);
        
        int x = 0;
        
        for (x = 0; x < ARRAY_LENGTH; x++)
        {
          cm2_array[x] = 0;
          cm3_array[x] = 0;
          cm4_array[x] = 0;
          cm5_array[x] = 0;
        }
}

void loop() {
  int i;
  if (millis() >= pingTimer) {         // Is it this sensor's time to ping?

    trigger2 = 1;
    trigger3 = 1;
    trigger4 = 1;
    trigger5 = 1;

    pingTimer += PING_INTERVAL;
    checkDetect();
    fill_arrays();
    print_all2();
 
   
    
    sonar1.ping_interrupt(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).   
    sonar2.ping_timer(sonar1.get_max_time());
    sonar3.ping_timer(sonar1.get_max_time());
    sonar4.ping_timer(sonar1.get_max_time());
    sonar5.ping_timer(sonar1.get_max_time());
    Timer1.resume();
    

  }
  
  if(!trigger2 && !trigger3 && !trigger4  &&!trigger5)
  {
      Timer1.stop();
  }
}

void fill_arrays()
{
   if (detect > 0)
   {
     if(cm2 <ALLOWED_DISTANCE)
     {
       cm2_array[counter] = cm2;
     }
     if(cm3 < ALLOWED_DISTANCE)
     {
       cm3_array[counter] = cm3;
     }
     if(cm4 < ALLOWED_DISTANCE)
     {
       cm4_array[counter] = cm4;
     }
     if(cm5 < ALLOWED_DISTANCE)
     {
       cm4_array[counter] = cm5;
     }
     if (counter < ARRAY_LENGTH)
       counter = counter + 1;
   }
    
}
void checkDetect()
{
  if (cm2 < ALLOWED_DISTANCE || cm3 < ALLOWED_DISTANCE || cm4 < ALLOWED_DISTANCE || cm5 < ALLOWED_DISTANCE)
  {
    detect=3; // setting how many times nothing is accepted
  }
  else if (cm2 >= ALLOWED_DISTANCE && cm3 >= ALLOWED_DISTANCE && cm4 >= ALLOWED_DISTANCE && cm5 >= ALLOWED_DISTANCE)
  {
    if (detect == 1)
    {
//      Serial.println();
//      Serial.print("Run: ");
//      Serial.print(runNum);
//      Serial.println();
      runNum ++;
      detect = 0;
      counter = 0;
      
      //print all values
      print_all();
      //Serial.flush();
      
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
//  if (trigger1 && sonar1.check_timer())
//  {
//    cm1 = sonar1.ping_result / US_ROUNDTRIP_CM;
//    trigger1 = 0;
//  }
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
  if (trigger5 && sonar5.check_timer())
  {
    cm5 = sonar5.ping_result / US_ROUNDTRIP_CM;
    trigger5 = 0;
  }
}
void print_all()
{
//  int number_values = 0;
//  String ss;
//  //second sensor
//  for(number_values = 0; number_values < 20; number_values++)
//  {
//    ss = ss + String(cm2_array[number_values]) + ",";
//    cm2_array[number_values] = 0;
//  }
//  ss = ss + ";";
//  //third sensor
//  for(number_values = 0; number_values < 20; number_values++)
//  {
//    ss = ss + String(cm3_array[number_values]) + ",";
//    cm3_array[number_values] = 0;
//
//  }
//  ss = ss + ";";
//  for(number_values = 0; number_values < 20; number_values++)
//  {
//    ss = ss +  String(cm4_array[number_values]) + ",";
//    cm4_array[number_values] = 0;
//  }
//  ss = ss + ";" + "\n";
//  Serial.print(ss);

  int number_values = 0;
  String ss;
  Serial.print("STG");
  
  //second sensor
  Serial.print("S01");
  for(number_values = 0; number_values < ARRAY_LENGTH; number_values++)
  {
    if (cm2_array[number_values] < 10)
    {
      ss = "00" + String(cm2_array[number_values]);
      Serial.print(ss);
      cm2_array[number_values] = 0;
    }
    else if (cm2_array[number_values] < 100)
    {
      ss = "0" + String(cm2_array[number_values]);
      Serial.print(ss);
      cm2_array[number_values] = 0;
    }
    else
    {
      ss = String(cm2_array[number_values]);
      Serial.print(ss);
      cm2_array[number_values] = 0;
    }
    
  }
  Serial.print("END");
  //third sensor
  Serial.print("S02");
  for(number_values = 0; number_values < ARRAY_LENGTH; number_values++)
  {
    if (cm3_array[number_values] < 10)
    {
      ss = "00" + String(cm3_array[number_values]);
      Serial.print(ss);
      cm3_array[number_values] = 0;
    }
    else if (cm3_array[number_values] < 100)
    {
      ss = "0" + String(cm3_array[number_values]);
      Serial.print(ss);
      cm3_array[number_values] = 0;
    }
    else
    {
      ss = String(cm3_array[number_values]);
      Serial.print(ss);
      cm3_array[number_values] = 0;
    }
    
  }
  Serial.print("END");
  //fourth sensor
  Serial.print("S03");
  for(number_values = 0; number_values < ARRAY_LENGTH; number_values++)
  {
    if (cm4_array[number_values] < 10)
    {
      ss = "00" + String(cm4_array[number_values]);
      Serial.print(ss);
      cm4_array[number_values] = 0;
    }
    else if (cm4_array[number_values] < 100)
    {
      ss = "0" + String(cm4_array[number_values]);
      Serial.print(ss);
      cm4_array[number_values] = 0;
    }
    else
    {
      ss = String(cm4_array[number_values]);
      Serial.print(ss);
      cm4_array[number_values] = 0;
    }
    
  }
  Serial.print("END");
  //fifth sensor
  Serial.print("S04");
  for(number_values = 0; number_values < ARRAY_LENGTH; number_values++)
  {
    if (cm5_array[number_values] < 10)
    {
      ss = "00" + String(cm5_array[number_values]);
      Serial.print(ss);
      cm5_array[number_values] = 0;
    }
    else if (cm5_array[number_values] < 100)
    {
      ss = "0" + String(cm5_array[number_values]);
      Serial.print(ss);
      cm5_array[number_values] = 0;
    }
    else
    {
      ss = String(cm5_array[number_values]);
      Serial.print(ss);
      cm5_array[number_values] = 0;
    }
    
  }
  Serial.print("END");
  Serial.print("ENG");
   
}
void print_all2()
{

  if (detect > 0)
  {
    if (cm2 < 90)
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
    
    if (cm3 < 90)
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
    
    if (cm4 < 90)
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
     if (cm5 < 90)
    {
      Serial.print("5");
      Serial.print("=");
      Serial.print(cm5);
      Serial.print("    ");   
    }
    else
    {
      Serial.print("        ");
    }
    Serial.println();
  }
  
}


