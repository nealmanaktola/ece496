#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GestureFinder.h"
#include <iostream>
#define INFINITY 1 << 25;
#define SCORE_THRESHOLD 500


Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
	{ { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } }, // LEFT TO RIGHT SWIPE
	{ { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } } // RIGHT TO LEFT SWIPE

};

//Dynamic Time Warping test with Random Vectors
int FindGesture(int left_sensor[20], int right_sensor[20], int down_sensor[20])
{
	int length = FindLength(left_sensor, right_sensor, down_sensor);
	int gesture_number = -1;
	bool isSimilar;
	int score;
	int previous_score = INFINITY;
	int dtw_score[3];


	//normalize values
	normalize(left_sensor, length);
	normalize(right_sensor, length);
	normalize(down_sensor, length);

	//normalize stored values
	for (int x = 0; x < NUMBER_OF_GESTURES; x++)
	{
		normalize(Stored_Gestures[x].LeftSensor, length);
		normalize(Stored_Gestures[x].RightSensor, length);
		normalize(Stored_Gestures[x].DownSensor, length);
	}

	for (int x = 0; x < NUMBER_OF_GESTURES; x++)
	{
		print_array("left_sensor", left_sensor, length);
		print_array("left_sensor_actual", Stored_Gestures[x].LeftSensor, 10);
		dtw_score[0] = dtw(left_sensor, Stored_Gestures[x].LeftSensor, 10, length);
		dtw_score[1] = dtw(right_sensor, Stored_Gestures[x].RightSensor, 10, length);
	    dtw_score[2] = dtw(down_sensor, Stored_Gestures[x].DownSensor, 10, length);

		isSimilar = (dtw_score[0] < SCORE_THRESHOLD) && (dtw_score[1] < SCORE_THRESHOLD) && (dtw_score[2] < SCORE_THRESHOLD);
		
		score = dtw_score[0] + dtw_score[2] + dtw_score[3];

		if (isSimilar & (score < previous_score))
			gesture_number = x;

		previous_score = score;
	}

	std::cin.get(); //TO KEEP CONSOLE OPEN
	return 0;
}

int minimum(int x, int y, int z)
{
	if (x <= y && x <= z)
		return x;

	if (y <= x && y <= z)
		return y;
	else
		return z;

}

int* normalize(int* arr, int n)
{
	int i;
	int min = INFINITY;
	//Find nonzero min
	for (i = 1; i < n; i++)
	{
		if (arr[i] && (arr[i] < min))
		{
			min = arr[i]; // dont want zeroes because they have different meaning
		
		}
	}
	min = min - 1;
	std::cout << min << std::endl;

	for (i = 0; i < n; i++)
	{
		if (arr[i]){
			arr[i] = arr[i] - min;

		}
	}
	return arr;
}
bool dtw(int *x, int *y, int n, int m)
{
	int** distance = new int *[n];
	int i, j;

	for (i = 0; i < n; i++)
		distance[i] = new int [m];

	//Initialize Matrix 
	for (i = 0; i < n; i++)
	{
		distance[i][0] = INFINITY;
	}
	for (j = 0; j < m; j++)
	{
		distance[0][j] = INFINITY;

	}
	distance[0][0] = 0;
	for (i = 1; i < n; i++)
	{
		for (j = 1; j < m; j++)
		{
			int cost = (x[i] - y[j]) * (x[i] - y[j]);
			distance[i][j] = cost + minimum(distance[i - 1][j], distance[i][j - 1], distance[i - 1][j - 1]);
		}
	}

	printf("minimum distance %d\n", distance[n - 1][m - 1]);

	return distance[n - 1][m - 1];

}
void print_array(char* name, int* x, int n)
{
	int i;

	printf("%s", name);
	for (i = 0; i < n; i++)
	{
		printf("%d,", x[i]);
	}
	printf("\n");
}
void print_gesture(Gesture input)
{
	print_array("left", input.LeftSensor, 10);
	print_array("right", input.RightSensor, 10);
	print_array("down", input.DownSensor, 10);

}
int FindLength(int left_sensor[20], int right_sensor[20], int down_sensor[20])
{
	bool first;
	bool second;
	bool third;

	for (int x = 0; x < 18; x++)
	{
		//if three 0s in a row, return index where zero starts
		first = (left_sensor[x] == 0) && (right_sensor[x] == 0) && (down_sensor[x] == 0);
		second = (left_sensor[x + 1] == 0) && (right_sensor[x + 1] == 0) && (down_sensor[x + 1] == 0);
		third = (left_sensor[x + 2] == 0) && (right_sensor[x + 2] == 0) && (down_sensor[x + 2] == 0);
		if (first && second && third)
		{
			std::cout << "length is" << x << std::endl;
			return x;
		}
		
	}

}