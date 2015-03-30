#include "stdafx.h"
#include "SensorParser.cpp"
#include "GestureFInder.h"

#define MAX_RUNS 3
struct Run {
	int ** sensorVals;
	int length;
};

class GestureCreator {

private:
	SensorParser m_parser;
public:
	GestureCreator(SensorParser& parser);
	void findReferencePattern(std::string gesture_name);

};

