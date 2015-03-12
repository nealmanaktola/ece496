#include "stdafx.h"
#include "SerialClass.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>


#define MAX_LEN 121 * 4


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

	void parseSensorStream(std::string allSensorStream, int ** sensorValues)
	{
		size_t pos = 0;
		int i = 0;

		while ((pos = allSensorStream.find("\n")) != std::string::npos) {
			std::string sensorStream = allSensorStream.substr(0, pos);
			size_t i_pos = 0;

			//Remove Padding 
			if ((i_pos = allSensorStream.find("X")) != std::string::npos)
				sensorStream = sensorStream.substr(0, i_pos);
			
			//Parse out numbers and add it to array
			int j = 0;
			while ((i_pos = sensorStream.find(",")) != std::string::npos)
			{
				int num = atoi((sensorStream.substr(0, i_pos)).c_str());

				if (num == 0)
					num = 200;
	
				sensorValues[i][j] = num;
				sensorStream.erase(0, i_pos + 1);
				j++;
			}

			i++;
			allSensorStream.erase(0, pos + 1);
		}
	}
	int** readData()
	{
		char in[MAX_LEN + 1];

		int bytes_read = 0;

		std::string sensorStream;

		while (bytes_read < MAX_LEN)
		{
			int numBytes = m_sp->ReadData(in, MAX_LEN-bytes_read);
			
			if (numBytes != -1)
			{
				bytes_read += numBytes;
				in[numBytes] = '\0';
				sensorStream = sensorStream + in;
			}
		}
		//std::cout << sensorStream;
		int ** sensorValues = new int *[4];
		for (int i = 0; i < 4; i++)
		{
			sensorValues[i] = new int[30];
		}
parseSensorStream(sensorStream, sensorValues);
		return sensorValues;
	}
	
};