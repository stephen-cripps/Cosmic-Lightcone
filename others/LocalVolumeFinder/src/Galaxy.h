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


struct Point {
	double x, y, z;
	Point(double x, double y, double z) :
		x(x), y(y), z(z) {
	}
};

class Galaxy {
public:
	Galaxy(double M, double x, double y, double z, double B);

	// Galaxy properties
	double mM;
	double mx, my, mz;
	double mB;	// absolute
	double mb;	// apparent

	void checkMass();
	void calcApparent(double d);	// Distance to the observer in Mpc

	bool isMW, isHeavy;

	static double MWMass; // 10^10 solar mass
	static double lowMassLimit;
	static double highMassLimit;

};

#endif /* GALAXY_H_ */
