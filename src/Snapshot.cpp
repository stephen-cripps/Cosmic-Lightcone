/*
 * Snapshot.cpp
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#include "Snapshot.h"

Snapshot::Snapshot() :
		mTAOid(0) {
}

Snapshot::Snapshot(int id) :
		mTAOid(id) {
}

bool Snapshot::load() {

	mParticles.reserve(MAX_RESERVE);
	// Reserve memory

	// Set Timer
	bool success = true;
	Timer loadingTimer;
	loadingTimer.start();

	// Format file path
	stringstream ss;
	ss << DIRECTORY_PATH;
	ss << "tao." << mTAOid << "." << "0.csv";

	// Open Snapshot file
	ifstream snapshotFile(ss.str().c_str());
	double lastTick = 0;

	int particleID = 0;
	// Read file
	if (snapshotFile.is_open()) {
		printf("Loading snapshot %s.\n", ss.str().c_str());
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
			mParticles.push_back(
					Particle(values[0], values[1], values[2], mTAOid,
							particleID++));
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

		printf("[SUCCESS] Loaded snapshot with %i galaxies, %.2f seconds.\n",
				(int) mParticles.size(), loadingTimer.getSec());
	} else {
		printf("[FAIL]: Unable to open snapshot file %s! \n", ss.str().c_str());
	}
	return success;
}

vector<Particle> Snapshot::getCone(double rMax, double rMin, double theta,
		double phi, double opening, Particle obs, vector<Particle> offsets) {
	vector<Particle> particles;
	for (vector<Particle>::iterator it = mParticles.begin();
			it != mParticles.end(); it++) {
		for (vector<Particle>::iterator pit = offsets.begin();
				pit != offsets.end(); pit++) {
			// Shift the box by offset
			double x = it->x + BOX_WIDTH * pit->x;
			double y = it->y + BOX_WIDTH * pit->y;
			double z = it->z + BOX_WIDTH * pit->z;

			// Position correction where observer is at the origin
			double tempX = x - obs.x;
			double tempY = y - obs.y;
			double tempZ = z - obs.z;
			// First rotation around z axis, clockwise by phi
			double tempX2 = tempX * cos(-phi) - tempY * sin(-phi);
			double tempY2 = tempX * sin(-phi) + tempY * cos(-phi);
			double tempZ2 = tempZ;
			// Then rotation around y axis, clockwise by theta
			double tempX3 = tempX2 * cos(-theta) + tempZ2 * sin(-theta);
			double tempY3 = tempY2;
			double tempZ3 = -tempX2 * sin(-theta) + tempZ2 * cos(-theta);
			// Calculating Spherical Polar
			double gR = sqrt(pow(tempX3, 2) + pow(tempY3, 2) + pow(tempZ3, 2));
			double gTheta = acos(tempZ3 / gR);

			if (gR > rMin && gR <= rMax && gTheta <= opening) {
				particles.push_back(Particle(x, y, z, it->sid, it->id));
			}
		}
	}
	return particles;
}

int Snapshot::getSize() {
	return mParticles.size();
}
