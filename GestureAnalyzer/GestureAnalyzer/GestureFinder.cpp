#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "GestureFinder.h"
#include "Common.h"
#include <iostream>

#define INFINITY 1 << 25
#define SCORE_THRESHOLD 2500



//Dynamic Time Warping test with Random Vectors

int FindGesture(Gesture Stored_Gestures[NUMBER_OF_GESTURES], int left_sensor[30], int right_sensor[30], int down_sensor[30], int up_sensor[30])
{
	/* TODO: Store normalized gestures in a file */
	//std::cout << "in findgesture";
/*	Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
		{ { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // LEFT TO RIGHT SWIPE
		{ { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // RIGHT TO LEFT SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, 10 }, //DOWN TO UP SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, 10 }, // UP TO DOWN SWIPE
		{ { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68, 200 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68, 200 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68, 200 }, { 26, 27, 28, 29, 34, 35, 40, 41, 41, 45, 46, 49, 51, 52, 54, 58, 62, 68, 200 }, 19 }, // up Z dierection
		{ { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, { 68, 62, 58, 54, 52, 51, 49, 46, 44, 41, 38, 36, 33, 31, 29, 28, 27, 26 }, 18 }, // down Z dierection
		{ { 5, 3, 3, 2, 5, 0, 4, 7, 5, 9, 6, 6}, { 6, 6, 2, 0, 0, 5, 10, 5, 7, 6, 7, 7}, { 177, 0, 1, 0, 0, 2, 0, 1, 2, 4, 5, 174}, { 177, 0, 0, 1, 2, 5, 5, 5, 3, 5, 5, 177 }, 11 } // CLAMP
	};*/
	/*Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
		{ { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // LEFT TO RIGHT SWIPE
		{ { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, 10 }, // RIGHT TO LEFT SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, 10 }, //DOWN TO UP SWIPE
		{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, 10 }, // UP TO DOWN SWIPE
		{ { 181, 181, 181, 0, 0, 0, 4, 4, 10, 11, 15, 19, 23, 27, 31, 40, 38, 38, 50, 55, 55, 64, 68, 181 }, { 183, 183, 183, 0, 3, 4, 4, 7, 9, 15, 15, 18, 18, 30, 30, 35, 43, 39, 49, 59, 183, 183, 183, 183 }, { 0, 1, 1, 3, 5, 6, 10, 10, 15, 16, 19, 24, 28, 33, 37, 39, 40, 50, 56, 188, 188, 188, 76, 76 }, { 183, 183, 0, 1, 183, 183, 3, 6, 11, 12, 16, 20, 24, 27, 183, 183, 44, 43, 48, 183, 183, 183, 183, 183 },24 }, //Z UP
		{ { 37, 31, 28, 22, 18, 17, 11, 7, 4, 4, 189, 189, 0, 189, 189, 189, 189, 189, 189, 189, 189, 189 }, { 30, 24, 21, 184, 184, 184, 8, 2, 0, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184 }, { 193, 193, 31, 25, 21, 17, 16, 12, 10, 6, 3, 2, 0, 7, 2, 10, 1, 4, 6, 13, 13, 19 }, { 33, 186, 186, 20, 17, 12, 7, 6, 0, 0, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186 },22 }, //Z DOWN
		{ { 181, 181, 3, 1, 0, 4, 3, 2, 4, 3, 5, 3, 5, 5, 8 }, { 179, 179, 179, 179, 1, 0, 2, 1, 1, 2, 1, 1, 1, 4, 4 }, { 0, 1, 0, 1, 1, 29, 4, 3, 2, 4, 4, 6, 9, 183, 183 }, { 180, 180, 180, 180, 180, 0, 0, 0, 2, 2, 3, 4, 5, 7, 180 }, 15} //SWIPE
	};*/
	/*
	Gesture Stored_Gestures[NUMBER_OF_GESTURES] = {
		{ { 0, 0, 0, 0, 0, 184 }, { 183, 183, 2, 0, 1, 4 }, { 185, 1, 0, 5, 5, 185 }, { 183, 6, 0, 1, 3, 183 }, 6	 }, //LEFT-RIGHT
		{ { 179, 179, 179, 4, 4, 0 }, { 2, 2, 0, 0, 2, 180 }, { 179, 179, 2, 0, 0, 179 }, { 178, 178, 3, 0, 1, 0 }, 6 }, //RIGHT-LEFT
		{ { 167, 167, 0, 0, 0, 0, 167 }, { 184,184,0,0,0,18,184,184,}, { 1, 0, 6, 0, 0, 0, 185 }, { 184, 4, 4, 0, 2, 0, 0 }, 7 }, //DOWN-UP
		{ { 186, 186, 0, 1, 1, 4, 186, 186 }, { 184, 184, 0, 0, 0, 18, 184, 184 }, { 187, 187, 4, 4, 2, 3, 0, 5 }, { 2, 0, 1, 0, 1, 3, 186, 186}, 8 } //UP_DOWN
	};
	*/
	
	int length = FindLength(left_sensor, right_sensor, down_sensor, up_sensor);
	int previous_score = INFINITY;
	std::vector<GestureScore> all_gestures;
	int dtw_score[4];

	if (length < 5)
	{
		DEBUG(("IDENTIFIED: GESTURE NOT FOUND\n\n"));
		return -1;
	}

	//error correction for input values
	fixInput(left_sensor, length);
	fixInput(right_sensor, length);
	fixInput(down_sensor, length);
	fixInput(up_sensor, length);
	print_array("LEFT sensor", left_sensor, length);
	print_array("RIGHT sensor", right_sensor, length);
	print_array("DOWN sensor", down_sensor, length);
	print_array("UP sensor", up_sensor, length);
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
		if (gs.majority >= max_majority)
		{
			max_majority = gs.majority;
			all_gestures.push_back(gs);
		}

	}

	int min_distance = INFINITY;
	int gesture_number = -1;

	for (int x = 0; x < all_gestures.size(); x++)
	{
		if (all_gestures[x].majority == max_majority)
		{
			if (all_gestures[x].score < min_distance)
			{
				gesture_number = all_gestures[x].gid;
				min_distance = all_gestures[x].score;
			}
		}
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
		if ((arr[x + 1] != 200 && arr[x - 1] != 200) && arr[x] == 200)
			arr[x] = arr[x - 1];
	}
}
int* normalize(int* arr, int n)
{
	int i;
	int min = INFINITY;

	for (i = 0; i < n; i++) 
	{
		if (arr[i] < min)
		{
			min = arr[i]; 
		
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
		//fourth = (left_sensor[x + 3] == 200) && (right_sensor[x + 3] == 200) && (down_sensor[x + 3] == 200) && (up_sensor[x + 3] == 200);

		if (first && second && third) //&& fourth)
		{
			if (x == 0)
				x = 1;
			return x;
		}
		
	}
	return 30;

}

