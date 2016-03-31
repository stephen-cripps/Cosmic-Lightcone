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
#include <sstream>		// stringstream
#include "Timer.h"		// Timer
using namespace std;

struct Particle {
	double x, y, z;
	int sid, id;
	Particle() :
		x(0), y(0), z(0), sid(0), id(0) {

	}
	Particle(double x, double y, double z) :
		x(x), y(y), z(z), sid(0), id(0) {
	}
	Particle(double x, double y, double z, int sid, int id) :
		x(x), y(y), z(z), sid(sid), id(id) {
	}
};

struct Box {
	double x, y, z, w, h, d;
	Box() :
		x(0), y(0), z(0), w(0), h(0), d(0) {
	}
	Box(double x, double y, double z, double w) :
		x(x), y(y), z(z), w(w), h(w), d(w) {
	}
	Box(double x, double y, double z, double w, double h, double d) :
		x(x), y(y), z(z), w(w), h(h), d(d) {
	}

};

class Snapshot {
public:
	Snapshot();
	Snapshot(int id);

	void setID(int id);
	bool load();

	vector<Particle> getCone(double rMax, double rMin, double theta,
			double phi, double opening, Particle obs, vector<Particle> offsets); // offsets are in units of the box width
	const static unsigned int PARTICLE_PARAMETERS_TOTAL = 4;
	const static unsigned int MAX_RESERVE = 10000000; // reverse memory for 10 million points

	static const int BOX_WIDTH = 500;

	int mTAOid;
	vector<Particle> mParticles;
	int getSize();

private:
	const static string DIRECTORY_PATH;
};

#endif /* SNAPSHOT_H_ */
