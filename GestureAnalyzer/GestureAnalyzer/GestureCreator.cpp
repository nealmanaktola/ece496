#include "stdafx.h"
#include "GestureCreator.h"
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <map>


GestureCreator::GestureCreator(SensorParser& parser) {
	m_parser = parser;
}




int findDistance(std::map<std::pair<int, int>, int>& distanceMap, std::vector<int **>& allRuns, std::vector<int>& allRunsLength, int ** pattern, int idx)
{
	int totalDistance = 0;
	for (int i = 0; i < MAX_RUNS; i++)
	{
		std::pair<int, int> pairDist;
		if (i != idx)
		{

			//Make sure the pair is sorted 
			if (i < idx)
				pairDist = std::make_pair(i, idx);
			else
				pairDist = std::make_pair(idx, i);

			if (distanceMap.find(pairDist) == distanceMap.end())
			{
				int ** otherPattern = allRuns[i];
				int fourSensorDist = 0;
				for (int j = 0; j < 4; j++)
				{
					int minDistance = dtw(pattern[j], otherPattern[j], allRunsLength[idx], allRunsLength[i]);
					fourSensorDist += minDistance;
				}
				distanceMap[pairDist] = fourSensorDist;
			}
			
			totalDistance += distanceMap[pairDist];
		}
	}
	return totalDistance;
}

//error correction for input values

//normalize values


void GestureCreator::findReferencePattern() {
	std::vector<int **> allRuns;
	std::vector<int> allRunsLength;

	for (int i = 0; i < MAX_RUNS; i++)
	{
		printf("Perform Sample %d\n", i);
		int ** sensorVals = m_parser.readData();

		int length = FindLength(sensorVals[0], sensorVals[1], sensorVals[2], sensorVals[3]);

		for (int j = 0; j < 4; j++)
		{
			fixInput(sensorVals[j], length);
			normalize(sensorVals[j], length);
			print_array(sensorLocation[j], sensorVals[j], length);
		}
	
		allRuns.push_back(sensorVals);
		allRunsLength.push_back(length);
	}

	std::vector<int **> normalizedAllRuns;

	std::map<std::pair<int, int>, int> distanceMap;

	int min = 1 << 28;
	int bestIndex;

	for (int i = 0; i < MAX_RUNS; i++)
	{

		int ** pattern = allRuns[i];
		
		int distance = findDistance(distanceMap, allRuns, allRunsLength, pattern, i);

		if (distance < min)
		{
			min = distance;
			bestIndex = i;
		}					
	}

	DEBUG(("\nFINAL FOUND \n"));
	printf("{ ");
	for (int i = 0; i < 4; i++)
	{
		//{ { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 19, 19, 19, 19, 19, 19, 200, 200 }, { 200, 200, 200, 200, 200, 19, 17, 16, 17, 19 }, { 19, 17, 16, 17, 19, 200, 200, 200, 200, 200 }, 10 }, // UP TO DOWN SWIPE
		printf("{ ");
		for (int j = 0; j < allRunsLength[bestIndex]; j++) {
			printf("%d,", allRuns[bestIndex][i][j]);

		}
		printf("}, ");
	}
	printf(" }\n");
}

