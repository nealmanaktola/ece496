#ifndef __GESTURE_FINDER__  
#define __GESTURE_FINDER__   
#define NUMBER_OF_GESTURES 2


struct Gesture
{
	int LeftSensor[10];
	int RightSensor[10];
	int DownSensor[10];
	int UpSensor[10];
};
struct GestureScore
{
	int gid;
	int majority;
	int score;
};

int minimum(int x, int y, int z);
int* normalize(int* arr, int n);
int dtw(int *x, int *y, int n, int m);
void print_array(char* name, int* x, int n);
int FindGesture(int left_sensor[30], int right_sensor[30], int down_sensor[30], int up_sensor[30]);
void print_gesture(Gesture input);
int FindLength(int left_sensor[30], int right_sensor[30], int down_sensor[30], int up_sensor[30]);
void delete_2d_array(int** x, int n);
void fixInput(int* arr, int n);


#endif 