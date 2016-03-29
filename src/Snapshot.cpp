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

vector<Particle> Snapshot::getCone(double rMax, double rMin, double theta,
		double phi, double opening, Particle obs, int xOffset, int yOffset,
		int zOffset) {
	printf("rMin: %f, rMax, %f, opening: %f\n", rMin, rMax, opening);
	vector<Particle> particles;
	for (vector<Particle>::iterator it = mParticles.begin();
			it != mParticles.end(); it++) {
		// Position correction where observer is at the origin
		double gX = it->x + BOX_WIDTH * xOffset - obs.x;
		double gY = it->y + BOX_WIDTH * yOffset - obs.y;
		double gZ = it->z + BOX_WIDTH * zOffset - obs.z;
		// First rotation around z axis, clockwise by phi
		gX = gX * cos(-phi) - gY * sin(-phi);
		gY = gX * sin(-phi) + gY * cos(-phi);
		// Then rotation around y axis, clockwise by theta
		gX = gX * cos(-theta) + gZ * sin(-theta);
		gZ = -gX * sin(-theta) + gZ * cos(-theta);
		// Calculating Spherical Polar
		double gR = sqrt(pow(gX, 2) + pow(gY, 2) + pow(gZ, 2));
		double gTheta = acos(gZ / gR);

		//printf("gR: %f, gTheta:%f\n", gR, gTheta);

		if (gR > rMin && gR <= rMax && gTheta <= opening) {
			particles.push_back(*it);
			//printf("Incone!!!\n");
		}
	}
	return particles;
}

int Snapshot::getSize() {
	return mParticles.size();
}
