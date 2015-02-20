// GestureAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialClass.h"
#include "SensorParser.cpp"
#include "GestureFinder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	SensorParser parser("\\\\.\\COM3");
	std::vector<int *> sensorValues;

	
	while (true)
	{
		parser.readData(sensorValues);
	}

	/*
	int	right_sensor_actual[20] = { 200, 200, 200, 200, 22, 24, 20, 24, 23, 26, 26, 200, 200, 200, 200, 200, 200, 200, 200, 200};
	int left_sensor_actual[20] = { 21, 21, 20, 20, 21, 21, 24, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int down_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int up_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	*/
	//int gesture = FindGesture(left_sensor_actual, right_sensor_actual, down_sensor_actual, up_sensor_actual);
	return 0;
}
