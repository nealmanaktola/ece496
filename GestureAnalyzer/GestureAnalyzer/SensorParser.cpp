#include "stdafx.h"
#include "SerialClass.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>

#define MAX_LEN 79 * 4

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

		std::cout << sensorStream;
		std::cout << std::endl;

	}
	
};