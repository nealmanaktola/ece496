// GestureAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialClass.h"
#include "SensorParser.cpp"
#include "GestureFinder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	SensorParser parser("\\\\.\\COM3");


	
	while (true)
	{
		int ** sensorValues = parser.readData();
		/*
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				std::cout << sensorValues[i][j] << ",";
			}
			std::cout << std::endl;
		}
		 */
		std::cout << std::endl;
		std::cout << std::endl;

		int gesture = FindGesture(sensorValues[0], sensorValues[1], sensorValues[2], sensorValues[3]);
		for (int i = 0; i < 4; i++)
		{
			delete[] sensorValues[i];
		}

		delete[] sensorValues;
	}

	/*
	int	right_sensor_actual[20] = { 200, 200, 200, 200, 22, 24, 20, 24, 23, 26, 26, 200, 200, 200, 200, 200, 200, 200, 200, 200};
	int left_sensor_actual[20] = { 21, 21, 20, 20, 21, 21, 24, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int down_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int up_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	*/
	
	return 0;
}

