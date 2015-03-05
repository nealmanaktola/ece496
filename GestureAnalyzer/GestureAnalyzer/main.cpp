// GestureAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialClass.h"
#include "GestureFinder.h"
#include "Common.h"
#include "GestureExecutor.h"
#include "GestureCreator.h"

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

int
WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
	SensorParser parser("\\\\.\\COM4");

	RedirectIOToConsole();
	
	while (true)
	{
		
		GestureCreator create(parser);

		//create.findReferencePattern();
		
		
		int ** sensorValues = parser.readData();

		int gesture = FindGesture(sensorValues[0], sensorValues[1], sensorValues[2], sensorValues[3]);
		if (gesture != -1)
		{
			GestureExecutor a;
			a.execute(gesture);
		}
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

