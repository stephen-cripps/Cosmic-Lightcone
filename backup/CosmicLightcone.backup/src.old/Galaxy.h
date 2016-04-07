/*
 * Galaxy.h
 *
 *  Created on: 23 Oct 2015
 *      Author: Steve
 */

#ifndef GALAXY_H_
#define GALAXY_H_

#include <math.h>	// atan, log
#include <cmath>	// squart

#include <stdio.h>

using namespace std;

class Galaxy {
public:
	Galaxy();
	Galaxy(double x, double y, double z);
	Galaxy(double mt, double x, double y, double z);
	Galaxy(double mt, double x, double y, double z, double b);
	Galaxy(double mt, double mb, double x, double y, double z, double vx,
			double vy, double vz);

	// Galaxy properties
	double mMt, mMb;
	double mx, my, mz;
	//double mVx, mVy, mVz;
	double mB;
	double mb;

	void checkMass();
	void calcApparent(double d);	// Distance to the observer in Mpc

	bool isMW, isHeavy;

	const static double MW_MASS = 6.4; // 10^10 solar mass

};

#endif /* GALAXY_H_ */
