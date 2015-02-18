#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "GestureFinder.h"
#include <iostream>
#define INFINITY 1 << 25;
#define SCORE_THRESHOLD 500

/*
Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
	{ { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } }, // LEFT TO RIGHT SWIPE
	{ { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } } // RIGHT TO LEFT SWIPE
};
*/

/* TODO: Store normalized gestures in a file */
Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
	{ { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 } }, // LEFT TO RIGHT SWIPE
	{ { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 } } // RIGHT TO LEFT SWIPE
};

//Dynamic Time Warping test with Random Vectors

int FindGesture(int left_sensor[20], int right_sensor[20], int down_sensor[20], int up_sensor[20])
{
	int length = FindLength(left_sensor, right_sensor, down_sensor, up_sensor);
	int gesture_number = -1;
	bool isSimilar;
	int majority;
	int score;
	int previous_score = INFINITY;
	std::vector<GestureScore> all_gestures;
	int dtw_score[4];

	//normalize values
	normalize(left_sensor, length);
	normalize(right_sensor, length);
	normalize(down_sensor, length);
	normalize(up_sensor, length);

	/*TODO: Remove this normalization, as it will be already normalized in file*/
	//normalize stored values
	for (int x = 0; x < NUMBER_OF_GESTURES; x++)
	{
		normalize(Stored_Gestures[x].LeftSensor, length);
		normalize(Stored_Gestures[x].RightSensor, length);
		normalize(Stored_Gestures[x].DownSensor, length);
		normalize(Stored_Gestures[x].UpSensor, length);
	}

	int max_majority = 0;

	for (int x = 0; x < NUMBER_OF_GESTURES; x++)
	{
		print_array("left_sensor", left_sensor, length);
		print_array("left_sensor_actual", Stored_Gestures[x].LeftSensor, 10);

		dtw_score[0] = dtw(left_sensor, Stored_Gestures[x].LeftSensor, length, 10);
		dtw_score[1] = dtw(right_sensor, Stored_Gestures[x].RightSensor, length, 10);
		dtw_score[2] = dtw(down_sensor, Stored_Gestures[x].DownSensor, length, 10);
		dtw_score[3] = dtw(up_sensor, Stored_Gestures[x].UpSensor, length, 10);

		GestureScore gs;
		/*TODO: add majority function*/
		gs.majority = (dtw_score[0] < SCORE_THRESHOLD) + (dtw_score[1] < SCORE_THRESHOLD) + (dtw_score[2] < SCORE_THRESHOLD) + (dtw_score[3] < SCORE_THRESHOLD);
		gs.score = dtw_score[0] + dtw_score[1] + dtw_score[2] + dtw_score[3];		
		gs.gid = x;
		if (gs.majority > max_majority)
		{
			max_majority = gs.majority;
			all_gestures.push_back(gs);
		}

	}

	int min_distance = INFINITY;
	int gid = -1;

	for (int x = 0; x < all_gestures.size(); x++)
	{
		if (all_gestures[x].majority == max_majority)
			if (all_gestures[x].score < min_distance)
				gesture_number = all_gestures[x].gid;
	}
	
	std::cout << "identified gesture " << gesture_number << std::endl;

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

	std::cout << min << std::endl;

	for (i = 0; i < n; i++)
	{
		if (arr[i]){
			arr[i] = arr[i] - min;

		}
	}
	return arr;
}

void delete_array(int** x, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] x[i];
	}
	delete[] x;
}
int dtw(int *x, int *y, int n, int m)
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

	int min = distance[n - 1][m - 1];
	
	delete_array(distance, n);
	return min;

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
	print_array("down", input.DownSensor, 10);

}

int FindLength(int left_sensor[20], int right_sensor[20], int down_sensor[20], int up_sensor[20])
{
	bool first;
	bool second;
	bool third;
	bool fourth;

	for (int x = 0; x < 18; x++)
	{
		//if three 0s in a row, return index where zero starts
		first = (left_sensor[x] == 200) && (right_sensor[x] == 200) && (down_sensor[x] == 200) && (up_sensor[x] == 200);
		second = (left_sensor[x + 1] == 200) && (right_sensor[x + 1] == 200) && (down_sensor[x + 1] == 200) && (up_sensor[x + 1] == 200);
		third = (left_sensor[x + 2] == 200) && (right_sensor[x + 2] == 200) && (down_sensor[x + 2] == 200) && (up_sensor[x + 2] == 200);
		fourth = (left_sensor[x + 3] == 200) && (right_sensor[x + 3] == 200) && (down_sensor[x + 3] == 200) && (up_sensor[x + 3] == 200);

		if (first && second && third && fourth)
		{
			std::cout << "length is" << x << std::endl;
			return x;
		}
		
	}

}