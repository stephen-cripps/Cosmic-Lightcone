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

class Lightcone {
public:
	Lightcone();
	void set(LightconeSettings settings);
	void setLabel(string str);
	bool loadRedshiftSteps();
	vector<Particle> getSegment(Snapshot& snap, double rMax, double rMin);

private:
	string mLabel;
	double mR, mTheta, mPhi, mOpening;
	vector<double> mRedshiftSteps;

};

#endif /* LIGHTCONE_H_ */
