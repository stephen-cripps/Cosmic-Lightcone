/*
 * Lightcone.h
 *
 *  Created on: 22 Mar 2016
 *      Author: eva
 */

#ifndef LIGHTCONE_H_
#define LIGHTCONE_H_

#include <stdio.h>		// printf
#include <math.h>		// pi
#include <fstream>		// Reading and writting files
#include <vector>		// vectors
#include <algorithm>	// Sort
#include <sstream>		// String stream
#include "Snapshot.h"

struct Observer {
	// Carry one here
};

struct LightconeSettings {
	const static double THETA_MAX = M_PI;
	const static double PHI_MAX = 2 * M_PI;
	const static double OPENING_MAX = M_PI / 4;

	double mR, mTheta, mPhi, mOpening;

	LightconeSettings() :
		mR(0), mTheta(0), mPhi(0), mOpening(0) {
	}
	LightconeSettings(double r, double theta, double phi, double opening) :
		mR(r), mTheta(theta), mPhi(phi), mOpening(opening) {
	}
	void set(double r, double theta, double phi, double opening) {
		mR = r;
		mTheta = theta;
		mPhi = phi;
		mOpening = opening;
	}
	void dump() {
		printf("Lightcone Setting: %.2f:%.2f:%.2f:%.2f \n", mR, mTheta, mPhi,
				mOpening);
	}
};

// -------------- Lightcone Class---------

class Lightcone {
public:
	Lightcone();
	void setLightcone(LightconeSettings settings);
	void setObserver(Particle obs);
	void setLabel(string str);
	bool loadRedshiftSteps();
	void generate();
	vector<Particle> getSegment(Snapshot& snap, double rMax, double rMin);
	void write();

public:
	static const int BOX_WIDTH = 500;
	static const int STARTING_TAO_NUM = 1409;

private:
	string mLabel;
	double mR, mTheta, mPhi, mOpening;
	Particle mObserver;
	vector<double> mRedshiftSteps;
	vector<Particle> mParticles;

private:
	int calcOffset(double);
	bool collide(Box a, Box b);
	void reverseRotation(vector<Particle>& par);
	Box makeBoxFromParticles(vector<Particle>& par);
	void shiftPointsByObserver(vector<Particle>& par, bool add);

	double getRFromRedshift(double z);

	// Debug
	void dumpParticles(vector<Particle>& par);

};

#endif /* LIGHTCONE_H_ */
