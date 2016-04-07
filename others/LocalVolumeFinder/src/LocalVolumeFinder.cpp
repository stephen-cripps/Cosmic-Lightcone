//============================================================================
// Name        : LocalVolumeFinder.cpp
// Author      : Hongbo Tian
// Version     :
// Copyright   : Hongbo Tian 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Snapshot.h"
#include "Galaxy.h"
using namespace std;

// Conditions
double Galaxy::MWMass = 6.4; // 10^10 solar mass Milkyway Candidate mass
double Galaxy::lowMassLimit = 0.8;
double Galaxy::highMassLimit = 1.2;
// Galaxies between the range of low*mass and high*mass are identified as mw candidates
// Galaxies above low*mass is identified as heavy

double LVLow = 300;
double LVHigh = 400;
double bBandLimit = 17.5;

bool writePointsToFile(string path, vector<Point> points);

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	string path = "/media/eva/Elements/Snapshot/tao.1409.0.csv";
	Snapshot snapshot;
	snapshot.load(path);

	// ----------------------------- Step   -----------------------------------

	// Local Volume Candidate Selection Process
	cout << "- - - Local Volume Candidate Selection Process - - -" << endl;
	cout << "Step one: Configuration Selection . . ." << endl;
	// Create a snap with only MW like galaxies
	Snapshot mwSnap;
	mwSnap.setGalaxies(snapshot.getCandidate());
	// Create a snap with only heavy galaxies
	Snapshot heavySnap;
	heavySnap.setGalaxies(snapshot.getHeavy());
	// Create two 2Mpc grid and cross reference
	MultiDimData mwNumGrid = mwSnap.getNumGrid(2);
	MultiDimData heavyNumGrid = heavySnap.getNumGrid(2);
	// Cross Reference
	vector<Point> candidates;
	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			for (int k = 0; k < 250; k++) {
				// if there are two mw candidates within a 2mpc box and no other galaxies
				if (heavyNumGrid.get(i, j, k) == 2
						&& mwNumGrid.get(i, j, k) == 2) {
					// Keep the point at the middle of the box
					candidates.push_back(Point(i + 1, j + 1, k + 1));
				}
			}
		}
	}
	printf("After Configuration Cross reference: %lu LV Candidates.\n",
			candidates.size());

	// ----------------------------- Step 2 -----------------------------------
	cout << "Step Two: Rough Cluster Detection . . ." << endl;
	// Correlate with number density
	int gridSize = 20;
	vector<Point> temp;
	MultiDimData numGrid = snapshot.getNumGrid(gridSize);
	for (vector<Point>::iterator it = candidates.begin();
			it != candidates.end(); it++) {
		int x, y, z;
		x = (it->x - (int) it->x % gridSize) / gridSize;
		y = (it->y - (int) it->y % gridSize) / gridSize;
		z = (it->z - (int) it->z % gridSize) / gridSize;

		if (numGrid.get(x, y, z) < (unsigned) (snapshot.getSize() / 15625)) {
			// have to be below average density
			temp.push_back(*it);
		}
	}
	candidates = temp;
	temp.clear();
	printf("After Rough Number Density Cross Reference: %lu LV Candidates\n",
			candidates.size());

	// ----------------------------- Step 3 -----------------------------------
	cout
			<< "Step Three: Fine Tune Cluster Detection & Apparent Magnitude Limitation . . ."
			<< endl;

	int progress = 0;
	for (vector<Point>::iterator it = candidates.begin();
			it != candidates.end(); it++) {
		vector<Galaxy> localVolume = snapshot.getPoint(it->x, it->y, it->z, 10);
		// if local number is less than the average density
		if (localVolume.size() < (unsigned) (snapshot.getSize() / 15625)) {
			// Magnitude calculation and limitation
			vector<Galaxy> localVolumeLimited;
			for (vector<Galaxy>::iterator nit = localVolume.begin();
					nit != localVolume.end(); nit++) {
				double d = sqrt(
						(it->x - nit->mx) * (it->x - nit->mx)
								+ (it->y - nit->my) * (it->y - nit->my)
								+ (it->z - nit->mz) * (it->z - nit->mz));
				nit->calcApparent(d);
				if (nit->mb < bBandLimit) {
					localVolumeLimited.push_back(*nit);
				}
			}

			printf("Local Volume Limited Size: %lu\n",
					localVolumeLimited.size());
			// visible number limitation
			if (localVolumeLimited.size() > LVLow
					&& localVolumeLimited.size() < LVHigh) {
				temp.push_back(*it);
			}

		}

		printf("Local Volume Size: %lu\n", localVolume.size());
		progress++;
		if (progress % 10 == 0) {
			printf("Progress: %d/%lu, Final %lu/%d\n", progress,
					candidates.size(), temp.size(), progress);
		}

		// Testing
		if (temp.size() > 20) {
			break;
		}
	}
	candidates = temp;
	temp.clear();
	printf("After Fine Tune Density Cross Reference Candidates: %lu\n",
			candidates.size());

	return 0;
}

bool writePointsToFile(string path, vector<Point> points) {
	bool success = true;

	ofstream file(path.c_str());

	if (file.is_open()) {
		file << "x, y, z\n";
		for (vector<Point>::iterator it = points.begin(); it != points.end();
				it++) {
			file << it->x << ", " << it->y << ", " << it->z << "\n";
		}

		file.close();
	} else {
		printf("Unable to output to file %s\n", path.c_str());
		success = false;
	}

	return success;
}
