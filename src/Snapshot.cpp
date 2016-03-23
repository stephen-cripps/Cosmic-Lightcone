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

bool Snapshot::load() {

	mParticles.reserve(MAX_RESERVE);
	// Reserve memory

	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Open Snapshot file
	ifstream snapshotFile(mPath.c_str());
	double lastTick = 0;

	// Read file
	if (snapshotFile.is_open()) {
		printf("Loading snapshot %s.\n", mPath.c_str());
		// Success on opening files
		string element;
		getline(snapshotFile, element); //Skips first line with parameter names
		while (!snapshotFile.eof()) { // Stop at the end of the file

			// Array of parameters
			double values[PARTICLE_PARAMETERS_TOTAL];

			// Skip the first two mass parameters
			getline(snapshotFile, element, ',');
			getline(snapshotFile, element, ',');

			// Read the next three position parameters
			for (unsigned int index = 0; index < PARTICLE_PARAMETERS_TOTAL - 1;
					index++) {
				getline(snapshotFile, element, ',');
				values[index] = atof(element.c_str());
			}

			// Adding the particles
			mParticles.push_back(Particle(values[0], values[1], values[2], 0));
			// Temp IDs are all 0
			// Skip to next line
			getline(snapshotFile, element, '\n');

			// Output Ticks
			if (loadingTimer.getSec() - lastTick >= 5.0) {
				printf(
						"Loading snapshot. . . %.2f seconds: %i particles, Speed: %.0f. \n",
						loadingTimer.getSec(), (int) mParticles.size(),
						(double) mParticles.size() / loadingTimer.getSec());
				lastTick = loadingTimer.getSec();
			}
		}

		// close the catalogue
		snapshotFile.close();

		printf("Loaded snapshot successfully, %i galaxies, %.2f seconds.\n",
				(int) mParticles.size(), loadingTimer.getSec());
	} else {
		printf("[FAIL]: Unable to open snapshot file %s! \n", mPath.c_str());
	}
	return success;
}

void Snapshot::align(double theta, double phi) {
	for (vector<Particle>::iterator it = mParticles.begin();
			it != mParticles.end(); it++) {
		// First rotation around z axis, clockwise by phi
		it->mX = it->mX * cos(-phi) - it->mY * sin(-phi);
		it->mY = it->mX * sin(-phi) + it->mY * cos(-phi);
		// Then rotation around y axis, clockwise by theta
		it->mX = it->mX * cos(-theta) + it->mZ * sin(-theta);
		it->mZ = -it->mX * sin(-theta) + it->mZ * cos(-theta);
		// Calculating Spherical Polar
		it->mR = sqrt(pow(it->mX, 2) + pow(it->mY, 2) + pow(it->mZ, 2));
		it->mTheta = acos(it->mZ / it->mR);
	}
}

int Snapshot::getSize() {
	return mParticles.size();
}
