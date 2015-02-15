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
		if (arr[i] && arr[i] < min)
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
	
	printf("minimum distance %d", distance[n-1][m-1]);
	
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
	//int x[] = {48,47,46,45,45,45,45,44,45,43,44,44,44,41,41,43,42,41,41,41,45,45,43}; //array x
	int x[] = {50,48,50,50,48,52,48,48,49,50,50,59}; //array x //FAST GESTURE
	int n = 12; //size of x
	
	//int y[] = {50,51,47,48,47,49,46,50,51,47,46,47,47,47,53,48,49}; //array y
	int y[] = {46,46,46,45,45,45,46,45,46,45,46,45,46,45,45,45,46,45,45,46}; //array y // SLOW LEFT-RIGHT GESTURE
	int m = 20;// size of y
	
	normalize(x,n);
	

	
	normalize(y,m);
	
	print_array("array x",x,n);
	print_array("array y",y,m);
	
	bool isSimilar = dtw(x,y,n,m);
	
	if (isSimilar)
		printf("Similar!");
	else
		printf("Not Similar!");
		
	return 0;
}
