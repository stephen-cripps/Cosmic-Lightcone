/*
 * Galaxy.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: Steve
 */

#include "Galaxy.h"

Galaxy::Galaxy(double M, double x, double y, double z, double B) :
		mM(M), mx(x), my(y), mz(z), mB(B), mb(0), isMW(false), isHeavy(false) {
	checkMass();
}

void Galaxy::checkMass() {
	if (mM > lowMassLimit * MWMass && mM < highMassLimit * MWMass) {
		isMW = true;
	} else {
		isMW = false;
	}

	if (mM > lowMassLimit * MWMass) {
		isHeavy = true;
	} else {
		isHeavy = false;
	}
}

void Galaxy::calcApparent(double d) {
	mb = mB + 5 * (log10(d * 1000000) - 1);
	printf("Absolute / Apparent / d (%.2f/%.2f/%.2f)\n", mB, mb, d);
}

