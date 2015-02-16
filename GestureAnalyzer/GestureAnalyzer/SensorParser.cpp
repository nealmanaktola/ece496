#include "stdafx.h"
#include "SerialClass.h"
#include <string>
#include <iostream>
#include <vector>

#define MAX_LEN 1024

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


	bool readData(std::vector<int *>& sensorValues)
	{
		char in[MAX_LEN];
		int numBytes = m_sp->ReadData(in, MAX_LEN);

		if (numBytes != -1)
		{
			//Assume Correct syntax;
			std::string allSensorStr = in;

			size_t pos = 0;
			int i = 0;

			while ((pos = allSensorStr.find(";")) != std::string::npos) {
				std::string sensorStream = allSensorStr.substr(0, pos);
				std::vector<int> values;

				size_t i_pos = 0;
				sensorValues.push_back(new int[20]);	
				int j = 0;
				while ((i_pos = sensorStream.find(",")) != std::string::npos)
				{
					int num = atoi((sensorStream.substr(0, pos)).c_str());
					sensorValues[i][j] = num;
					sensorStream.erase(0, i_pos + 1);
					j++;
				}

				i++;
				
				allSensorStr.erase(0, pos + 1);
			}
			return true;
		}
		
		return false;
	}



};