#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITY 1 << 25;

//Dynamic Time Warping test with Random Vectors

int min (int x, int y, int z)
{
	if (x <= y && x <= z)
		return x;	
		
	if (y <= x && y <= z)
		return y;		
	else
		return z;

}

int normalize(int* arr, int n)
{
	int i;
	int min = arr[0];
	//Find nonzero min
	for (i = 1; i < n; i++)
	{
		if (arr[i] && (arr[i] < min))
		{
			min = arr[i];
		}
	}	
	
	for (i = 0; i < n; i++)
	{
		if (arr[i])
			arr[i] = arr[i] - min;
	}
}
bool dtw(int *x, int *y, int n, int m)
{
	int** distance = (int **) malloc(sizeof(int *) * n);	
	int i,j;
		
	for (i = 0; i < n; i++)
		distance[i] = (int *) malloc(sizeof(int) * m);
	
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
			distance[i][j] = cost + min(distance[i-1][j], distance[i][j-1], distance[i-1][j-1]);
		}
	}
	
	printf("minimum distance %d\n", distance[n-1][m-1]);
	
	return (distance[n-1][m-1] < 75);
		
}
void print_array(char* name, int* x, int n)
{
	int i;
	
	printf("%s",name);
	for (i = 0; i < n; i++)
	{
		printf("%d,",x[i]);
	}
	printf("\n");
}
int main(int argc, char **argv)
{
	int x[] = {20,20,0,0,20,20}; //array x
	//int x[] = {50,48,50,50,48,52,48,48,49,50,50,59}; //array x //FAST GESTURE
	int n = 6; //size of x
	
	int y[] = {0,0,0,20,20,20,0,0}; //array y // SLOW LEFT-RIGHT GESTURE
	int m = 8;// size of y
  
  print_array("Array One: ",x,n);
	print_array("Array Two: ",y,m);
	
	bool isSimilar = dtw(x,y,n,m);
	
	if (isSimilar)
		printf("Similar!");
	else
		printf("Not Similar!");
    

  //int down_sensor_normal[10][10];
	
  // int left_sensor_normal[10] = {19,17,16,17,19,0,0,0,0,0};
  // int right_sensor_normal[10] = {0,0,0,0,0,19,17,16,17,19};
  // int up_sensor_normal[10] = {0,0,19,19,19,19,19,19,0,0};

  
  // int left_sensor_actual[11] = {0,0,0,0,22,24,20,24,23,26,26};
  // int right_sensor_actual[11] = {21,21,20,20,21,21,24,0,0,0};
  // int up_sensor_actual[11] = {0,20,18,21,20,22,22,0,0,0,0};

  
  // bool isSimilar = dtw(left_sensor_normal,left_sensor_actual,10, 11) 
  // & dtw(right_sensor_normal,right_sensor_actual,10, 11)
  // & dtw(up_sensor_normal,up_sensor_actual,10, 11);
	
	// if (isSimilar)
		// printf("Similar!");
	// else
		// printf("Not Similar!");
		
	return 0;
}
