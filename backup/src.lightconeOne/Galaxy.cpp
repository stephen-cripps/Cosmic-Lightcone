/*
 * Galaxy.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: Steve
 */

#include "Galaxy.h"

Galaxy::Galaxy() {
	// TODO Auto-generated constructor stub
}

// Simple Galaxy construction
Galaxy::Galaxy(double x, double y, double z) :
		mMt(0), mMb(0), mx(x), my(y), mz(z), mVx(0), mVy(0), mVz(0), isMW(
				false), isHeavy(false) {
}

Galaxy::Galaxy(double mt, double x, double y, double z) :
		mMt(mt), mMb(0), mx(x), my(y), mz(z), mVx(0), mVy(0), mVz(0), isMW(
				false) {
	checkMass();
}

Galaxy::Galaxy(double mt, double mb, double x, double y, double z, double vx,
		double vy, double vz) :
		mMt(mt), mMb(mb), mx(x), my(y), mz(z), mVx(vx), mVy(vy), mVz(vz) {
	checkMass();
}

void Galaxy::checkMass() {
	if (mMt > 0.8 * MW_MASS && mMt < 1.2 * MW_MASS) {
		isMW = true;
	} else {
		isMW = false;
	}
	if (mMt > 0.8 * MW_MASS) {
		isHeavy = true;
	} else {
		isHeavy = false;
	}
}

