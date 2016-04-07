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
#include "Timer.h"		// Timer
#include "MultiDimData.h"	// 3D data structure

using namespace std;

class Snapshot {
public:
	Snapshot();
	Snapshot(string path);

	void setPath(string path);
	void setGalaxies(vector<Galaxy> galaxies);
	bool loadPos();	// Load only position data
	bool loadPosMt();	// Load position and total mass only
	bool loadFull();
	bool checkIntegrity();
	MultiDimData getNumGrid(int gridSize);
	MultiDimData getMassGrid(int gridSize);
	MultiDimData getOverDensity(int gridSize);

	vector<Galaxy> getCandidate();
	vector<Galaxy> getHeavy();
	vector<Galaxy> getPoint(double x, double y, double z, double radius);

	bool writePos(vector<Galaxy> galaxies, string path);

	const static unsigned int PARAMETERS_POS = 3;
	const static unsigned int PARAMETERS_POSMT = 4;
	const static unsigned int PARAMETERS_TOTAL = 8;
	const static unsigned int BOX_SIZE = 500; //Mpc
	const static unsigned int INTEGRITY_GRID_SIZE = 50; //Mpc
	const static unsigned int MAX_RESERVE = 18000000; // reverse memory for 20 million points

	string mPath;
	vector<Galaxy> mGalaxies;
	int getSize();

	virtual ~Snapshot();

	// Temp
	void candidateCount();
};

#endif /* SNAPSHOT_H_ */
