// GestureAnalyzer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "SerialClass.h"
#include "GestureFinder.h"
#include "Common.h"
#include "GestureExecutor.h"
#include "GestureCreator.h"
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <iostream>

Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
	{ { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // LEFT TO RIGHT SWIPE
	{ { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // RIGHT TO LEFT SWIPE
	{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, 10 }, //DOWN TO UP SWIPE
	{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, 10 }, // UP TO DOWN SWIPE
	{ { 181, 181, 181, 0, 0, 0, 4, 4, 10, 11, 15, 19, 23, 27, 31, 40, 38, 38, 50, 55, 55, 64, 68, 181 }, { 183, 183, 183, 0, 3, 4, 4, 7, 9, 15, 15, 18, 18, 30, 30, 35, 43, 39, 49, 59, 183, 183, 183, 183 }, { 0, 1, 1, 3, 5, 6, 10, 10, 15, 16, 19, 24, 28, 33, 37, 39, 40, 50, 56, 188, 188, 188, 76, 76 }, { 183, 183, 0, 1, 183, 183, 3, 6, 11, 12, 16, 20, 24, 27, 183, 183, 44, 43, 48, 183, 183, 183, 183, 183 }, 24 }, //Z UP
	{ { 37, 31, 28, 22, 18, 17, 11, 7, 4, 4, 189, 189, 0, 189, 189, 189, 189, 189, 189, 189, 189, 189 }, { 30, 24, 21, 184, 184, 184, 8, 2, 0, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184 }, { 193, 193, 31, 25, 21, 17, 16, 12, 10, 6, 3, 2, 0, 7, 2, 10, 1, 4, 6, 13, 13, 19 }, { 33, 186, 186, 20, 17, 12, 7, 6, 0, 0, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186 }, 22 }, //Z DOWN
	{ { 181, 181, 3, 1, 0, 4, 3, 2, 4, 3, 5, 3, 5, 5, 8 }, { 179, 179, 179, 179, 1, 0, 2, 1, 1, 2, 1, 1, 1, 4, 4 }, { 0, 1, 0, 1, 1, 29, 4, 3, 2, 4, 4, 6, 9, 183, 183 }, { 180, 180, 180, 180, 180, 0, 0, 0, 2, 2, 3, 4, 5, 7, 180 }, 15 } //SWIPE
};

void populate_default_values()
{
	std::ifstream input("gesture_numbers.txt");
	for (std::string line; getline(input, line);)
	{
		const char *str = line.c_str();
		char *cstr = new char[line.length() + 1];

		strcpy(cstr, str);

		char * pch;
		pch = strtok(cstr, ";");

		// Find which value to change to new value
		int gestureNumber;
		for (gestureNumber = 0; gestureNumber < NUMBER_OF_GESTURES; gestureNumber++)
		{
			if (!strcmp(pch, gestureDescription[gestureNumber]))
			{
				printf("Gesture NUM %d\n", gestureNumber);
				break;
			}
		}
		int elementNumber = 0;
		pch = strtok(NULL, ";");
		//Go through each sensor
		for (int sensorNumber = 0; pch != NULL; sensorNumber++)
		{
			elementNumber = 0;
			std::string element = "";
			for (int i = 0; i < strlen(pch); i++)
			{
				
				if (pch[i] == ' ')
				{
					if (sensorNumber == 0)
						Stored_Gestures[gestureNumber].LeftSensor[elementNumber] = atoi(element.c_str());
					else if (sensorNumber == 1)
						Stored_Gestures[gestureNumber].RightSensor[elementNumber] = atoi(element.c_str());
					else if (sensorNumber == 2)
						Stored_Gestures[gestureNumber].DownSensor[elementNumber] = atoi(element.c_str());
					else if (sensorNumber == 3)
						Stored_Gestures[gestureNumber].UpSensor[elementNumber] = atoi(element.c_str());
					printf("%s\n", element.c_str());
					element = "";
					elementNumber++;
					continue;
				}
					
				element = element + pch[i];
				
			}
			Stored_Gestures[gestureNumber].length = elementNumber;
			printf("%d\n", elementNumber);
			printf("%s\n", pch);

			pch = strtok(NULL, ";");
		}
		print_array("LEFT sensor", Stored_Gestures[gestureNumber].LeftSensor, elementNumber);
		print_array("RIGHT sensor", Stored_Gestures[gestureNumber].RightSensor, elementNumber);
		print_array("UP sensor", Stored_Gestures[gestureNumber].UpSensor, elementNumber);
		print_array("DOWN sensor", Stored_Gestures[gestureNumber].DownSensor, elementNumber);
		delete[] cstr;

	}
}
static const WORD MAX_CONSOLE_LINES = 500;
void RedirectIOToConsole()
{
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stdout = *fp;

	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stderr = *fp;

	setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();
}
void GestureExecuteTest() {
	GestureExecutor a;
	while (true) {
		Sleep(3000);
		a.execute(5);
	}
}

int
WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
	

	RedirectIOToConsole();
	

	SensorParser parser("\\\\.\\COM4");

	while (true)
	{

		int mode = 1;
		if (mode == 0)
		{

			GestureCreator create(parser);
			create.findReferencePattern("LEFT-RIGHT");

			//populates the array of values that will be used for comparisons
			populate_default_values(); 
		}
		else if (mode == 1)
		{

			int ** sensorValues = parser.readData();

			LARGE_INTEGER frequency;
			if (::QueryPerformanceFrequency(&frequency) == FALSE)
				throw "foo";

			LARGE_INTEGER start;
			if (::QueryPerformanceCounter(&start) == FALSE)
				throw "foo";

			int gesture = FindGesture(Stored_Gestures, sensorValues[0], sensorValues[1], sensorValues[2], sensorValues[3]);

			LARGE_INTEGER end;
			if (::QueryPerformanceCounter(&end) == FALSE)
				throw "foo";

			double interval = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

			//DEBUG(("time: %f\n", interval));

			if (gesture != -1)
			{
				DEBUG(("Gestures being executed"));
				//GestureExecutor a;
				//a.execute(gesture);
			}
			for (int i = 0; i < 4; i++)
			{
				delete[] sensorValues[i];
			}

			delete[] sensorValues;
		}
	}
	
	/*
	int	right_sensor_actual[20] = { 200, 200, 200, 200, 22, 24, 20, 24, 23, 26, 26, 200, 200, 200, 200, 200, 200, 200, 200, 200};
	int left_sensor_actual[20] = { 21, 21, 20, 20, 21, 21, 24, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int down_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int up_sensor_actual[20] = { 200, 20, 18, 21, 20, 22, 22, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	*/
	
	return 0;
}

