/*
 * Snapshot.cpp
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#include "Snapshot.h"

Snapshot::Snapshot() {
	// TODO Auto-generated constructor stub
}

Snapshot::Snapshot(string path) :
	mPath(path) {
}

void Snapshot::setGalaxies(vector<Galaxy> galaxies) {
	mGalaxies = galaxies;
}

bool Snapshot::loadPos() {

	mGalaxies.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Open Snapshot file
	ifstream catalogue(mPath.c_str());
	double lastTick = 0;

	// Read file
	if (catalogue.is_open()) {

		printf("Note: Snapshot: loading POS %s.\n", mPath.c_str());

		// Success on opening files
		string element;
		getline(catalogue, element); //Skips first line with parameter names

		while (!catalogue.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARAMETERS_POS];

			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			for (int i = 0; i < PARAMETERS_POS; i++) {
				getline(catalogue, element, ',');
				values[i] = atof(element.c_str());
			}
			getline(catalogue, element, '\n');
			// Skips the first tow variable as there are the mass terms
			// Then read the three position data that follows
			// Then read untile the end of the line

			// Adding Galaxies
			mGalaxies.push_back(Galaxy(values[0], values[1], values[2]));

			// Output Ticks
			if (loadingTimer.getSec() - lastTick >= 5.0) {
				printf(
						"Note: Snapshot loading POS . . . %.2f seconds: %i galaxies, Speed: %.0f. \n",
						loadingTimer.getSec(), (int) mGalaxies.size(),
						(double) mGalaxies.size() / loadingTimer.getSec());
				lastTick = loadingTimer.getSec();
			}

		}
		// close the catalogue
		catalogue.close();
		printf(
				"Note: Snapshot: Catalogues Reading Successful, %i galaxies, %.2f seconds.\n",
				(int) mGalaxies.size(), loadingTimer.getSec());
	} else {
		printf("Warning: Snapshot failed to open file %s! \n", mPath.c_str());
	}
	return success;
}

bool Snapshot::loadPosMt() {

	mGalaxies.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Open Snapshot file
	ifstream catalogue(mPath.c_str());
	double lastTick = 0;

	// Read file
	if (catalogue.is_open()) {

		printf("Note: Snapshot: loading POSMT %s.\n", mPath.c_str());

		// Success on opening files
		string element;
		getline(catalogue, element); //Skips first line with parameter names

		while (!catalogue.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARAMETERS_POSMT];

			getline(catalogue, element, ',');
			values[0] = atof(element.c_str());
			getline(catalogue, element, ',');
			for (int i = 1; i < PARAMETERS_POSMT; i++) {
				getline(catalogue, element, ',');
				values[i] = atof(element.c_str());
			}
			getline(catalogue, element, '\n');
			// Skips the first tow variable as there are the mass terms
			// Then read the three position data that follows
			// Then read untile the end of the line

			// Adding Galaxies
			mGalaxies.push_back(
					Galaxy(values[0], values[1], values[2], values[3]));

			// Output Ticks
			if (loadingTimer.getSec() - lastTick >= 5.0) {
				printf(
						"Note: Snapshot loading POSMT . . . %.2f seconds: %i galaxies, Speed: %.0f. \n",
						loadingTimer.getSec(), (int) mGalaxies.size(),
						(double) mGalaxies.size() / loadingTimer.getSec());
				lastTick = loadingTimer.getSec();
			}

		}
		// close the catalogue
		catalogue.close();
		printf(
				"Note: Snapshot: Catalogues Reading Successful, %i galaxies, %.2f seconds.\n",
				(int) mGalaxies.size(), loadingTimer.getSec());
	} else {
		printf("Warning: Snapshot failed to open file %s! \n", mPath.c_str());
	}
	return success;
}

bool Snapshot::loadPosMtB() {

	mGalaxies.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Open Snapshot file
	ifstream catalogue(mPath.c_str());
	double lastTick = 0;

	// Read file
	if (catalogue.is_open()) {

		printf("Note: Snapshot: loading POSMTB %s.\n", mPath.c_str());

		// Success on opening files
		string element;
		getline(catalogue, element); //Skips first line with parameter names

		while (!catalogue.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARAMETERS_POSMTB];
			getline(catalogue, element, ',');
			values[0] = atof(element.c_str());
			getline(catalogue, element, ',');
			for (int i = 1; i < PARAMETERS_POSMTB; i++) {
				getline(catalogue, element, ',');
				values[i] = atof(element.c_str());
			}
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			getline(catalogue, element, ',');
			values[4] = atof(element.c_str());
			getline(catalogue, element, '\n');
			// Read the first
			// Skip the second
			// Read the next three
			// Skip the next four
			// Read the next
			// Then read untile the end of the line

			// Adding Galaxies
			mGalaxies.push_back(
					Galaxy(values[0], values[1], values[2], values[3], values[4]));

			// Output Ticks
			if (loadingTimer.getSec() - lastTick >= 5.0) {
				printf(
						"Note: Snapshot loading POSMTB . . . %.2f seconds: %i galaxies, Speed: %.0f. \n",
						loadingTimer.getSec(), (int) mGalaxies.size(),
						(double) mGalaxies.size() / loadingTimer.getSec());
				lastTick = loadingTimer.getSec();
			}

		}
		// close the catalogue
		catalogue.close();
		printf(
				"Note: Snapshot: Catalogues Reading Successful, %i galaxies, %.2f seconds.\n",
				(int) mGalaxies.size(), loadingTimer.getSec());
	} else {
		printf("Warning: Snapshot failed to open file %s! \n", mPath.c_str());
	}
	return success;
}

bool Snapshot::loadFull() {

	mGalaxies.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Open Snapshot file
	ifstream catalogue(mPath.c_str());
	double lastTick = 0;

	// Read file
	if (catalogue.is_open()) {

		printf("Note: Snapshot: loading FULL %s.\n", mPath.c_str());

		// Success on opening files
		string element;
		getline(catalogue, element); //Skips first line with parameter names

		while (!catalogue.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARAMETERS_TOTAL];

			// Reading the index
			for (unsigned int index = 0; index < PARAMETERS_TOTAL; index++) {

				if (index == PARAMETERS_TOTAL - 1) {
					getline(catalogue, element, '\n');
				} else {
					getline(catalogue, element, ',');
				}
				values[index] = atof(element.c_str());
			}

			// Adding Galaxies
			mGalaxies.push_back(
					Galaxy(values[0], values[1], values[2], values[3],
							values[4], values[5], values[6], values[7]));

			// Output Ticks
			if (loadingTimer.getSec() - lastTick >= 5.0) {
				printf(
						"Note: Snapshot loading FULL . . . %.2f seconds: %i galaxies, Speed: %.0f. \n",
						loadingTimer.getSec(), (int) mGalaxies.size(),
						(double) mGalaxies.size() / loadingTimer.getSec());
				lastTick = loadingTimer.getSec();
			}

		}

		// close the catalogue
		catalogue.close();

		printf(
				"Note: Snapshot: Catalogues Reading Successful, %i galaxies, %.2f seconds.\n",
				(int) mGalaxies.size(), loadingTimer.getSec());
	} else {
		printf("Warning: Snapshot failed to open file %s! \n", mPath.c_str());
	}
	return success;
}

bool Snapshot::checkIntegrity() {
	bool success = true;
	if (mGalaxies.size() == 0) {
		printf("Error: Snapshot: No galaxy data for integrity check.");
		success = false;
	} else {

		// Maximum number of cells in one direction
		int gridNum = BOX_SIZE / INTEGRITY_GRID_SIZE;

		// Average Number of Gal per Cell
		double cellAvg = (double) mGalaxies.size() / (gridNum * gridNum
				* gridNum);

		// Integrity density grid
		MultiDimData integrityGrid(gridNum);
		for (vector<Galaxy>::iterator it = mGalaxies.begin(); it
				!= mGalaxies.end(); it++) {
			int i, j, k;
			i = ((int) it->mx - (int) it->mx % INTEGRITY_GRID_SIZE)
					/ INTEGRITY_GRID_SIZE;
			j = ((int) it->my - (int) it->my % INTEGRITY_GRID_SIZE)
					/ INTEGRITY_GRID_SIZE;
			k = ((int) it->mz - (int) it->mz % INTEGRITY_GRID_SIZE)
					/ INTEGRITY_GRID_SIZE;
			//cout << i << ":" << j << ":" << k << endl;
			// Correction for galaxies on the edge of the box
			if (i == 10) {
				i = 0;
			}
			if (j == 10) {
				j = 0;
			}
			if (k == 10) {
				k = 0;
			}

			//				cout << it->mx << ": " << it->my << ": " << it->mz << endl;
			integrityGrid.fill(i, j, k, integrityGrid.get(i, j, k) + 1);
		}
		// Checking Integrity
		for (int i = 0; i < gridNum; i++) {
			for (int j = 0; j < gridNum; j++) {
				for (int k = 0; k < gridNum; k++) {
					if (integrityGrid.mData[i][j][k] < cellAvg / 4) {
						printf(
								"Error: Snapshot: Strange missing void at (%i, %i, %i)!\n",
								i * INTEGRITY_GRID_SIZE,
								j * INTEGRITY_GRID_SIZE,
								k * INTEGRITY_GRID_SIZE);
						success = false;
					}
				}
			}
		}
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
		for (vector<Galaxy>::iterator it = mGalaxies.begin(); it
				!= mGalaxies.end(); it++) {
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

MultiDimData Snapshot::getMassGrid(int gridSize) {
	int gridNum = BOX_SIZE / gridSize;
	MultiDimData massGrid(gridNum);
	if (BOX_SIZE % gridSize != 0) {
		printf(
				"Error: Snapshot: massGrid Size Must be a factor of the Box Size!/n");
		// Correction to gridSize
		gridSize = BOX_SIZE / gridNum;
	} else {
		for (vector<Galaxy>::iterator it = mGalaxies.begin(); it
				!= mGalaxies.end(); it++) {
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
			massGrid.fill(i, j, k, massGrid.get(i, j, k) + it->mMt);
		}
	}
	return massGrid;
}

MultiDimData Snapshot::getOverDensity(int gridSize) {
	int gridNum = BOX_SIZE / gridSize;
	MultiDimData numGrid(gridNum);
	MultiDimData overDensityGrid(gridNum);
	if (BOX_SIZE % gridSize != 0) {
		printf(
				"Error: Snapshot: Overdensity Grid Size Must be a factor of the Box Size!/n");
		// Correction to gridSize
		gridSize = BOX_SIZE / gridNum;
	} else {
		for (vector<Galaxy>::iterator it = mGalaxies.begin(); it
				!= mGalaxies.end(); it++) {
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
		// Over density Caluclation
		double cellAvg = (double) mGalaxies.size() / (gridNum * gridNum
				* gridNum);
		cout << "Cell Average: " << cellAvg << endl;
		for (int i = 0; i < gridNum; i++) {
			for (int j = 0; j < gridNum; j++) {
				for (int k = 0; k < gridNum; k++) {
					overDensityGrid.fill(i, j, k,
							numGrid.get(i, j, k) / cellAvg);
					//					cout << "Overdensity: " << overDensityGrid.get(i, j, k)
					//							<< flush;
					//					cout << " Galaxy Number: " << numGrid.get(i, j, k) << endl;
				}
			}
		}
		cout << "Cell Average: " << cellAvg << endl;
	}

	return overDensityGrid;
}

int Snapshot::getSize() {
	return mGalaxies.size();
}

Snapshot::~Snapshot() {
	// TODO Auto-generated destructor stub
}

vector<Galaxy> Snapshot::getCandidate() {
	vector<Galaxy> candidates;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end(); it++) {
		if (it->isMW) {
			candidates.push_back(*it);
		}
	}
	return candidates;
}
vector<Galaxy> Snapshot::getHeavy() {
	vector<Galaxy> heavy;
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end(); it++) {
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
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end(); it++) {
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
	for (vector<Galaxy>::iterator it = mGalaxies.begin(); it != mGalaxies.end(); it++) {
		if (it->mx < x + radius && it->mx > x - radius && it->my < y + radius
				&& it->my > y - radius && it->mz < z + radius && it->mz > z
				- radius) {
			galaxies.push_back(*it);
		}

	}
	return galaxies;
}

bool Snapshot::writePos(vector<Galaxy> galaxies, string path) {
	bool success = true;

	ofstream outputFile(path.c_str());

	if (outputFile.is_open()) {
		for (vector<Galaxy>::iterator it = galaxies.begin(); it
				!= galaxies.end(); it++) {
			outputFile << it->mx << "," << it->my << "," << it->mz << endl;
		}
	} else {
		printf("Warning: Failed to write to file! %s \n", path.c_str());
	}
	outputFile.close();
	return success;
}
