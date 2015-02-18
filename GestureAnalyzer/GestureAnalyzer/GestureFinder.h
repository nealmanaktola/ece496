#ifndef __GESTURE_FINDER__  
#define __GESTURE_FINDER__   
#define NUMBER_OF_GESTURES 2

struct Gesture
{
	int LeftSensor[10];
	int RightSensor[10];
	int DownSensor[10];
	//int UpSensor[10];
};

int minimum(int x, int y, int z);
int* normalize(int* arr, int n);
bool dtw(int *x, int *y, int n, int m);
void print_array(char* name, int* x, int n);
int FindGesture(int left_sensor[20], int right_sensor[20], int down_sensor[20]);
void print_gesture(Gesture input);
int FindLength(int left_sensor[20], int right_sensor[20], int down_sensor[20]);



#endif 