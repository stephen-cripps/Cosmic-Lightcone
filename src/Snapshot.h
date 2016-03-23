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
#include <math.h>		// sin and cos
#include "Timer.h"		// Timer

using namespace std;

struct Particle {
	double mX, mY, mZ;
	int mID;
	// Spherical polar, don't need phi
	double mR, mTheta;

	Particle(double mx, double my, double mz, int id) :
			mX(mx), mY(my), mZ(mz), mID(id), mR(0), mTheta(0) {
	}
};

class Snapshot {
public:
	Snapshot();
	Snapshot(string path);

	void setPath(string path);
	bool load();

	void align(double theta, double phi);

	const static unsigned int PARTICLE_PARAMETERS_TOTAL = 4;
	const static unsigned int MAX_RESERVE = 10000000; // reverse memory for 10 million points

	string mPath;
	vector<Particle> mParticles;
	int getSize();

};

#endif /* SNAPSHOT_H_ */
