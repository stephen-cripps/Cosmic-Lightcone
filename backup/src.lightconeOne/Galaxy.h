/*
 * Galaxy.h
 *
 *  Created on: 23 Oct 2015
 *      Author: Steve
 */

#ifndef GALAXY_H_
#define GALAXY_H_

#include <math.h>	// atan
#include <cmath>	// squart

#include <stdio.h>

using namespace std;

class Galaxy {
public:
	Galaxy();
	Galaxy(double x, double y, double z);
	Galaxy(double mt, double x, double y, double z);
	Galaxy(double mt, double mb, double x, double y, double z, double vx,
			double vy, double vz);

	// Galaxy properties
	double mMt, mMb;
	double mx, my, mz;
	double mVx, mVy, mVz;

	void checkMass();

	bool isMW, isHeavy;

	const static double MW_MASS = 6.4; // 10^10 solar mass

};

#endif /* GALAXY_H_ */
