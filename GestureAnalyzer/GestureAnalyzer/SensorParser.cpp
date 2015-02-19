#include "stdafx.h"
#include "SerialClass.h"
#include <string>
#include <iostream>
#include <vector>

#define MAX_LEN 3

class SensorParser {
private:
	Serial* m_sp;
public:
	SensorParser();
	SensorParser(char* comPort)
	{
		m_sp = new Serial(comPort);
		if (m_sp->IsConnected())
			std::cout << "Not connected" << std::endl;
	};

	int * readSensorValues()
	{
		char in[MAX_LEN];
		int numBytes;
		int* valueList = new int[30];
		int i = 0;
		while (true)
		{
			if ((numBytes = m_sp->ReadData(in, MAX_LEN)) != -1)
			{
				if (!strncmp("END", in,3))
				{
					break;
				}
				else
				{
					int val = atoi(in);
					valueList[i] = val;
					i++;
				}
			}

		}
		return valueList;
	}
	bool readData(std::vector<int *>& sensorValues)
	{
		char in[MAX_LEN];
		int numBytes;

		//New Gesture if STG;
		if ((numBytes = m_sp->ReadData(in, MAX_LEN) != -1) && !(strncmp(in, "STG", MAX_LEN)))
		{
			while (true)
			{
				if ((numBytes = m_sp->ReadData(in, MAX_LEN)) != -1)
				{
					if (!strncmp("S0", in,2))
					{
						int * sensorValueList = readSensorValues();
						sensorValues.push_back(sensorValueList);

					}
					else if (!strncmp("ENG", in,3))
					{
						break;
					}

				}

			}
			return true;
		}
		return false;
	}



};