#ifndef __COMMON__  
#define __COMMON__  
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#define DEBUG(args) (printf args)
//#define DEBUG(args) 
static char* sensorLocation[] = { "LEFT", "RIGHT", "DOWN", "UP" };
static char* gestureDescription[] = { "LEFT-RIGHT", "RIGHT-LEFT", "DOWN-UP", "UP-DOWN", "ZOOM IN", "ZOOM OUT"};
#endif
