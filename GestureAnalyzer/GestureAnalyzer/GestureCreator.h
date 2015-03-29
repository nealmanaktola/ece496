#include "stdafx.h"
#include "SensorParser.cpp"
#include "GestureFInder.h"

#define MAX_RUNS 6
struct Run {
	int ** sensorVals;
	int length;
};

class GestureCreator {

private:
	SensorParser m_parser;
public:
	GestureCreator(SensorParser& parser);
	void findReferencePattern();

};

