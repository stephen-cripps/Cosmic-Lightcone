/*
 * Lightcone.cpp
 *
 *  Created on: 22 Mar 2016
 *      Author: eva
 */

#include "Lightcone.h"

Lightcone::Lightcone() {
}

void Lightcone::set(LightconeSettings settings) {
	mR = settings.mR;
	mTheta = settings.mTheta;
	mPhi = settings.mPhi;
	mOpening = settings.mOpening;
}

void Lightcone::setLabel(string str) {
	mLabel = str;
}

bool Lightcone::loadRedshiftSteps() {
	bool success = true;
	string redshiftFilePath = "/media/eva/Elements/Snapshot/redshiftStep";
	ifstream redShiftFile(redshiftFilePath.c_str());
	if (redShiftFile.is_open()) {
		// Cleaning current redshiftsteps
		mRedshiftSteps.clear();
		while (!redShiftFile.eof()) {
			string rawInput;
			getline(redShiftFile, rawInput);
			mRedshiftSteps.push_back(atof(rawInput.c_str()));
		}
		// Sort the steps from small to big
		sort(mRedshiftSteps.begin(), mRedshiftSteps.end());
		printf("[SUCCESS] Loading redshift steps successful\n");
	} else {
		printf("[FAIL] Unable to load redshift step file %s\n",
				redshiftFilePath.c_str());
	}
	return success;
}

vector<Particle> Lightcone::getSegment(Snapshot& snap, double rMax,
		double rMin) {
	vector<Particle> inCone;
	// Core stuff here
	return inCone;
}
