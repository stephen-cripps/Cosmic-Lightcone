//============================================================================
// Name        : LightconeOne.cpp
// Author      : anthemEdge
// Version     :
// Copyright   : Hongbo Tian 2015
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>		// Read and write files
#include <sstream>		// String Stream
#include <algorithm>	// Max_element
#include "Snapshot.h"	// Snapshot Class
#include "Timer.h" 		// Custom timer wrapper
#include "MultiDimData.h"	// 3d data Structure
using namespace std;

struct Point {
	double x, y, z;

	Point(double x, double y, double z) :
		x(x), y(y), z(z) {
	}

};

bool writePoints(vector<Point> points, string path);

int main() {
	Timer runTime;
	runTime.start();

	bool testMode = false;
	bool isLinux = false;

	// Auto file path construction
	const string WINDOWS_PATH = "H:\\";
	const string NAME = "tao.1409.0.csv";
	const string LINUX_PATH = "/media/eva/Elements";

	stringstream pathSS;
	string dirSep;
	if (isLinux) {
		pathSS << LINUX_PATH;
		dirSep = "/";

	} else {
		pathSS << WINDOWS_PATH;
		dirSep = "\\";
	}
	pathSS << dirSep;

	if (testMode) {
		pathSS << "NewSnapshotMini";
	} else {
		pathSS << "NewSnapshotFull";
	}
	pathSS << dirSep;
	pathSS << NAME;

	// Load the first Snapshot
	Snapshot testSnapshot(pathSS.str());
	testSnapshot.loadPosMtB(); // Loading only position and total mass
	testSnapshot.candidateCount();

	/*
	 cout << "- - - Number of Galaxies in Grids Calculation - - -" << endl;
	 int gridSizes[6] = { 4, 5, 10, 20, 25, 50 };
	 for (int i = 0; i < 6; i++) {
	 MultiDimData testNumGrid = testSnapshot.getNumGrid(gridSizes[i]);
	 stringstream ss;
	 ss << gridSizes[i] << "MpcGalaxyNumberGrid.csv";
	 testNumGrid.writeToFile(ss.str().c_str());

	 MultiDimData testMassGrid = testSnapshot.getMassGrid(gridSizes[i]);
	 ss.clear();
	 ss.str("");
	 ss << gridSizes[i] << "MpcMassGrid.csv";
	 testMassGrid.writeToFile(ss.str().c_str());
	 }
	 */

	// Local Volume Candidate Selection Process
	cout << "- - - Local Volume Candidate Selection Process - - -" << endl;

	cout << "Step one: Configuration Selection . . ." << endl;
	// Create a snap with only MW like galaxies
	Snapshot mwSnap;
	mwSnap.setGalaxies(testSnapshot.getCandidate());
	// Create a snap with only heavy galaxies
	Snapshot heavySnap;
	heavySnap.setGalaxies(testSnapshot.getHeavy());
	// Create two 2Mpc grid and cross reference
	MultiDimData mwNumGrid = mwSnap.getNumGrid(2);
	MultiDimData heavyNumGrid = heavySnap.getNumGrid(2);
	// Cross Reference
	vector<Point> lvCandidates;
	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			for (int k = 0; k < 250; k++) {
				if (heavyNumGrid.get(i, j, k) == 2 && mwNumGrid.get(i, j, k)
						== 2) {
					// Keep the point at the middle of the box
					lvCandidates.push_back(Point(i + 1, j + 1, k + 1));
				}
			}
		}
	}
	printf("Configuration Cross reference: %u LV Candidates.\n",
			lvCandidates.size());

	cout << "Step Two: Rough Cluster Detection . . ." << endl;
	// Correlate with number density
	int gridSize = 20;
	vector<Point> lvCan;
	MultiDimData testNumGrid = testSnapshot.getNumGrid(gridSize);
	for (vector<Point>::iterator it = lvCandidates.begin(); it
			!= lvCandidates.end(); it++) {
		int x, y, z;
		x = (it->x - (int) it->x % gridSize) / gridSize;
		y = (it->y - (int) it->y % gridSize) / gridSize;
		z = (it->z - (int) it->z % gridSize) / gridSize;
		if (testNumGrid.get(x, y, z) < (unsigned) (testSnapshot.getSize()
				/ 15625)) {
			lvCan.push_back(*it);
		}
	}
	printf("Rough Number Density Cross Reference: %u LV Candidates\n",
			lvCan.size());

	lvCandidates = lvCan;
	lvCan.clear();
	cout << "Step Three: Fine Tune Cluster Detection . . ." << endl;
	// Fine Tune Number Density
	Timer clusterTimer;
	clusterTimer.start();
	int progress = 0;
	for (vector<Point>::iterator it = lvCandidates.begin(); it
			!= lvCandidates.end(); it++) {
		vector<Galaxy> localVolume = testSnapshot.getPoint(it->x, it->y, it->z,
				10);
		// Check for Clustering
		// if local number is less than twice of the average density
		if (localVolume.size() < (unsigned) (testSnapshot.getSize() / 15625)) {
			lvCan.push_back(*it);
			vector<Galaxy> localVolumeLimited;
			for (vector<Galaxy>::iterator nit = localVolume.begin(); nit
					!= localVolume.end(); nit++) {
				double d = (it->x - nit->mx) * (it->x - nit->mx) + (it->y
						- nit->my) * (it->y - nit->my) + (it->z - nit->mz)
						* (it->z - nit->mz);
				nit->calcApparent(d);
				if (nit->mb < 17.5) {
					localVolumeLimited.push_back(*nit);
				}
			}
			stringstream ss;
			ss << "LVCandidates";
			ss << dirSep;
			ss << localVolumeLimited.size() << ".";
			ss << it->x << "." << it->y << "." << it->z << ".csv";
		}

		//			testSnapshot.writePos(localVolume, ss.str());
		if (progress >= 20) {
			break;
		}

		progress++;
		if (((int) clusterTimer.getSec() % 10) == 0) {
			printf(
					"Time: %f, Progress: %d/%u, Time Left: %f\n",
					clusterTimer.getSec(),
					progress,
					lvCandidates.size(),
					(lvCandidates.size() - progress) * (clusterTimer.getSec()
							/ progress));
		}
	}

	writePoints(lvCan, "FinalLVCandidates");
	printf("Final Local Volume Candidates: %u\n", lvCan.size());

	cout << "Total run time: " << runTime.getSec() << endl;
	return 0;
}

bool writePoints(vector<Point> points, string path) {
	bool success = true;
	ofstream outputFile(path.c_str());

	if (outputFile.is_open()) {
		for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
			outputFile << it->x << "," << it->y << "," << it->z << endl;
		}
	} else {
		printf("Warning: Failed to write to file! %s \n", path.c_str());
	}
	outputFile.close();
	return success;
}
