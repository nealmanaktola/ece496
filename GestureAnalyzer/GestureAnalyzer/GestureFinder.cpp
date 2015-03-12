#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "GestureFinder.h"
#include "Common.h"
#include <iostream>
#define INFINITY 1 << 25
#define SCORE_THRESHOLD 1000
#define NUMBER_OF_GESTURES 6
//#define NUMBER_OF_GESTURES 6

/*
Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
	{ { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } }, // LEFT TO RIGHT SWIPE
	{ { 0, 0, 0, 0, 0, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 0, 0, 0, 0, 0 }, { 0, 0, 19, 19, 19, 19, 19, 19, 0, 0 } } // RIGHT TO LEFT SWIPE
};
*/



//Dynamic Time Warping test with Random Vectors

int FindGesture(int left_sensor[30], int right_sensor[30], int down_sensor[30], int up_sensor[30])
{
	/* TODO: Store normalized gestures in a file */

	Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
		{ { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // LEFT TO RIGHT SWIPE
		{ { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // RIGHT TO LEFT SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, 10 }, //DOWN TO UP SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, 10 }, // UP TO DOWN SWIPE
		{ { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68 }, 18 }, // up Z dierection
		{ { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, 18 } // down Z dierection
	};

	/*
	Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
		{ { 0, 0, 0, 0, 0, 184 }, { 183, 183, 2, 0, 1, 4 }, { 185, 1, 0, 5, 5, 185 }, { 183, 6, 0, 1, 3, 183 }, 6	 }, //LEFT-RIGHT
		{ { 179, 179, 179, 4, 4, 0 }, { 2, 2, 0, 0, 2, 180 }, { 179, 179, 2, 0, 0, 179 }, { 178, 178, 3, 0, 1, 0 }, 6 }, //RIGHT-LEFT
		{{ 167, 167, 0, 0, 0, 0, 167, }, { 183, 16, 2, 0, 2, 2, 183, }, { 1, 0, 6, 0, 0, 0, 185 }, { 184, 4, 4, 0, 2, 0, 0 }, 7 } //DOWN-UP
	};
	*/

	int length = FindLength(left_sensor, right_sensor, down_sensor, up_sensor);
	int gesture_number = -1;
	bool isSimilar;
	int majority;
	int score;
	int previous_score = INFINITY;
	std::vector<GestureScore> all_gestures;
	int dtw_score[4];

	//error correction for input values
	fixInput(left_sensor, length);
	fixInput(right_sensor, length);
	fixInput(down_sensor, length);
	fixInput(up_sensor, length);

	//normalize values
	normalize(left_sensor, length);
	normalize(right_sensor, length);
	normalize(down_sensor, length);
	normalize(up_sensor, length);

	/*TODO: Remove this normalization, as it will be already normalized in file*/
	//normalize stored values
	
	for (int x = 0; x < (NUMBER_OF_GESTURES); x++)
	{
		normalize(Stored_Gestures[x].LeftSensor, Stored_Gestures[x].length);
		normalize(Stored_Gestures[x].RightSensor, Stored_Gestures[x].length);
		normalize(Stored_Gestures[x].DownSensor, Stored_Gestures[x].length);
		normalize(Stored_Gestures[x].UpSensor, Stored_Gestures[x].length);
	}
	
	int max_majority = 0;


	for (int x = 0; x < NUMBER_OF_GESTURES; x++)
	{

		dtw_score[0] = dtw(left_sensor, Stored_Gestures[x].LeftSensor, length, Stored_Gestures[x].length);
		dtw_score[1] = dtw(right_sensor, Stored_Gestures[x].RightSensor, length, Stored_Gestures[x].length);
		dtw_score[2] = dtw(down_sensor, Stored_Gestures[x].DownSensor, length, Stored_Gestures[x].length);
		dtw_score[3] = dtw(up_sensor, Stored_Gestures[x].UpSensor, length, Stored_Gestures[x].length);

		GestureScore gs;
		/*TODO: add majority function*/

		gs.majority = (dtw_score[0] < SCORE_THRESHOLD) + (dtw_score[1] < SCORE_THRESHOLD) + (dtw_score[2] < SCORE_THRESHOLD) + (dtw_score[3] < SCORE_THRESHOLD);
		gs.score = dtw_score[0] + dtw_score[1] + dtw_score[2] + dtw_score[3];	
		DEBUG(("GESTURE: %s distance %d %d %d %d %d\n", gestureDescription[x], dtw_score[0], dtw_score[1],dtw_score[2],dtw_score[3], gs.score));
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
	if (gesture_number != -1)
	{
		DEBUG(("IDENTIFIED: %s\n\n", gestureDescription[gesture_number]));
	}
	else
		DEBUG(("IDENTIFIED: GESTURE NOT FOUND\n\n"));
	//std::cin.get(); //TO KEEP CONSOLE OPEN
	return gesture_number;
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
void fixInput(int* arr, int n)
{
	for (int x = 1; x < n - 1; x++)
	{
		// if numbers of both side of current element is not 200, it is probably an error
		if ((arr[x + 1] != 200 || arr[x - 1] != 200) && arr[x] == 200)
			arr[x] = arr[x - 1];
	}
}
int* normalize(int* arr, int n)
{
	int i;
	int min = INFINITY;
	//Find nonzero min
	for (i = 0; i < n; i++) // why was this array i = 1?
	{
		if (arr[i] && (arr[i] < min))
		{
			min = arr[i]; // dont want zeroes because they have different meaning
		
		}
	}

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
<<<<<<< HEAD

=======
	
>>>>>>> origin/master
	//printf("minimum distance %d\n", distance[n - 1][m - 1]);

	int min = distance[n - 1][m - 1];
	
	delete_array(distance, n);
	return min;

}


void print_array(char* name, int* x, int n)
{
	int i;

	DEBUG(("%s", name));
	for (i = 0; i < n; i++)
	{
		DEBUG(("%d,", x[i]));
	}
	DEBUG(("\n"));
}

int FindLength(int left_sensor[30], int right_sensor[30], int down_sensor[30], int up_sensor[30])
{
	bool first;
	bool second;
	bool third;
	bool fourth;

	for (int x = 0; x < 27; x++)
	{
		//if three 0s in a row, return index where zero starts
		first = (left_sensor[x] == 200) && (right_sensor[x] == 200) && (down_sensor[x] == 200) && (up_sensor[x] == 200);
		second = (left_sensor[x + 1] == 200) && (right_sensor[x + 1] == 200) && (down_sensor[x + 1] == 200) && (up_sensor[x + 1] == 200);
		third = (left_sensor[x + 2] == 200) && (right_sensor[x + 2] == 200) && (down_sensor[x + 2] == 200) && (up_sensor[x + 2] == 200);
		fourth = (left_sensor[x + 3] == 200) && (right_sensor[x + 3] == 200) && (down_sensor[x + 3] == 200) && (up_sensor[x + 3] == 200);

		if (first && second && third && fourth)
		{
			if (x == 0)
				x = 1;
			return x;
		}
		
	}

}

