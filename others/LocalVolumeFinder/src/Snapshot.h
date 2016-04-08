/*
 * Snapshot.h
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#ifndef SNAPSHOT_H_
#define SNAPSHOT_H_

#include <iostream>		// Cout
#include <vector>		// Vector Containers
#include <fstream>		// Reading and writing files
#include <stdlib.h>		// atof - convert string to doubles
#include "Galaxy.h"		// Galaxies
#include "MultiDimData.h"	// 3D data structure

using namespace std;

class Snapshot {
public:
	Snapshot();

	void setGalaxies(vector<Galaxy> galaxies);
	bool load(string path);	// Load only position data
	MultiDimData getNumGrid(int gridSize);

	vector<Galaxy> getCandidate();
	vector<Galaxy> getHeavy();
	vector<Galaxy> getPoint(double x, double y, double z, double radius);

	bool writePos(vector<Galaxy> galaxies, string path);
	const static unsigned int PARAMETERS_TOTAL = 5;
	const static unsigned int BOX_SIZE = 500; //Mpc
	const static unsigned int MAX_RESERVE = 18000000; // reverse memory for 20 million points

	vector<Galaxy> mGalaxies;
	int getSize();

	// Temp
	void candidateCount();
};

#endif /* SNAPSHOT_H_ */
