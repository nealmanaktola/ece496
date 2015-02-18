// GestureAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialClass.h"
#include "SensorParser.cpp"
#include "GestureFinder.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	SensorParser parser("\\\\.\\COM3");
	std::vector<int *> sensorValues;


	while (true)
	{
		int isValid = parser.readData(sensorValues);

		if (isValid)
		{
			for (int i = 0; i < sensorValues.size(); i++)
			{
				for (int j = 0; j < 20; j++)
				{
					std::cout << sensorValues[i][j] << ",";
				}
				printf("\n");
			}

		}
	}*/
	int left_sensor_actual[20] = { 0, 0, 0, 0, 22, 24, 20, 24, 23, 26, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int right_sensor_actual[20] = { 21, 21, 20, 20, 21, 21, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int up_sensor_actual[20] = { 0, 20, 18, 21, 20, 22, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int gesture = FindGesture(left_sensor_actual, right_sensor_actual, up_sensor_actual);
	return 0;
}

