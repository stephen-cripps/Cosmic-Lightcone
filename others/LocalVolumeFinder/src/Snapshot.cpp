/*
 * Snapshot.cpp
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#include "Snapshot.h"

Snapshot::Snapshot() {
}

void Snapshot::setGalaxies(vector<Galaxy> galaxies) {
	mGalaxies = galaxies;
}

bool Snapshot::load(string path) {

	mGalaxies.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	// Open Snapshot file
	ifstream catalogue(path.c_str());

	// Read file
	if (catalogue.is_open()) {
		printf("Loading Snapshot %s.\n", path.c_str());

		// Success on opening files
		string element;
		getline(catalogue, element); //Skips first line with parameter names

		while (!catalogue.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARAMETERS_TOTAL];
			getline(catalogue, element, ',');
			// First Element is mass
			values[0] = atof(element.c_str());
			// Skip the next element
			getline(catalogue, element, ',');
			// Three Position data
			for (int i = 1; i <= 3; i++) {
				getline(catalogue, element, ',');
				values[i] = atof(element.c_str());
			}
			// Skip the next 4 (velocity and uband)
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			// Load bBand
			getline(catalogue, element, ',');
			values[4] = atof(element.c_str());
			// Skip to the end of the line
			getline(catalogue, element, '\n');

			// Adding Galaxies
			mGalaxies.push_back(
					Galaxy(values[0], values[1], values[2], values[3],
							values[4]));
		}
		// close the catalogue
		catalogue.close();
		printf("Note: Snapshot: Catalogues Reading Successful, %i galaxies.\n",
				(int) mGalaxies.size());
	} else {
		printf("Warning: Snapshot failed to open file %s! \n", path.c_str());
	}
	return success;
}

MultiDimData Snapshot::getNumGrid(int gridSize) {
	int gridNum = BOX_SIZE / gridSize;
	MultiDimData numGrid(gridNum);
	if (BOX_SIZE % gridSize != 0) {
		printf(
				"Error: Snapshot: numGrid Size Must be a factor of the Box Size!/n");
		// Correction to gridSize
		gridSize = BOX_SIZE / gridNum;
	} else {
		for (vector<Galaxy>::iterator it = mGalaxies.begin();
				it != mGalaxies.end(); it++) {
			int i, j, k;
			i = ((int) it->mx - (int) it->mx % gridSize) / gridSize;
			j = ((int) it->my - (int) it->my % gridSize) / gridSize;
			k = ((int) it->mz - (int) it->mz % gridSize) / gridSize;
			// Correction for galaxies on the edge of the box
			if (i == gridNum) {
				i = 0;
			}
			if (j == gridNum) {
				j = 0;
			}
			if (k == gridNum) {
				k = 0;
			}
			numGrid.fill(i, j, k, numGrid.get(i, j, k) + 1);
		}
	}

	return numGrid;
}

int Snapshot::getSize() {
	return mGalaxies.size();
}

vector<Galaxy> Snapshot::getCandidate() {
	vector<Galaxy> candidates;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end();
			it++) {
		if (it->isMW) {
			candidates.push_back(*it);
		}
	}
	return candidates;
}
vector<Galaxy> Snapshot::getHeavy() {
	vector<Galaxy> heavy;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end();
			it++) {
		if (it->isHeavy) {
			heavy.push_back(*it);
		}
	}
	return heavy;
}

// Temp
void Snapshot::candidateCount() {
	int mwCount, heavyCount;
	mwCount = heavyCount = 0;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end();
			it++) {
		if (it->isMW) {
			mwCount++;
		}
		if (it->isHeavy) {
			heavyCount++;
		}
	}
	printf("Note: Snapshot: MW Candidate: %d, Heavy Galaxies: %d \n", mwCount,
			heavyCount);
}

vector<Galaxy> Snapshot::getPoint(double x, double y, double z, double radius) {
	vector<Galaxy> galaxies;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end();
			it++) {
		if (it->mx < x + radius && it->mx > x - radius && it->my < y + radius
				&& it->my > y - radius && it->mz < z + radius
				&& it->mz > z - radius) {
			galaxies.push_back(*it);
		}

	}
	return galaxies;
}

bool Snapshot::writePos(vector<Galaxy> galaxies, string path) {
	bool success = true;

	ofstream outputFile(path.c_str());

	if (outputFile.is_open()) {
		for (vector<Galaxy>::iterator it = galaxies.begin();
				it != galaxies.end(); it++) {
			outputFile << it->mx << "," << it->my << "," << it->mz << endl;
		}
	} else {
		printf("Warning: Failed to write to file! %s \n", path.c_str());
	}
	outputFile.close();
	return success;
}
