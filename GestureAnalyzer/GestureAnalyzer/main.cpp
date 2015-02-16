// GestureAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialClass.h"
#include "SensorParser.cpp"


int _tmain(int argc, _TCHAR* argv[])
{
	
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
	}
	return 0;
}

