/*
 * Lightcone.cpp
 *
 *  Created on: 22 Mar 2016
 *      Author: eva
 */

#include "Lightcone.h"

Lightcone::Lightcone() {
}

void Lightcone::setLightcone(LightconeSettings settings) {
	mR = settings.mR;
	mTheta = settings.mTheta;
	mPhi = settings.mPhi;
	mOpening = settings.mOpening;
}
void Lightcone::setObserver(Particle obs) {
	mObserver = obs;
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

void Lightcone::generate() {
	printf(
			"Generating Lightcone with [R:%.2f, Theta: %.2f, Phi: %.2f, Opening: %.2f]\n",
			mR, mTheta, mPhi, mOpening);
	mParticles.clear();
	int fileIndex = 0;
	double rMin = 0;
	for (vector<double>::iterator it = mRedshiftSteps.begin();
			it != mRedshiftSteps.end(); it++, fileIndex++) {
		double r = *it * (1 + *it) * 4109.6;
		if (r < mR) {
			stringstream ss;
			ss << "/media/eva/Elements/Snapshot/" << "tao.";
			ss << STARTING_TAO_NUM + fileIndex;
			ss << ".0.csv";
			printf("Loading %d, for z= %f, r = %f\n",
					STARTING_TAO_NUM + fileIndex, *it, r);
			// Load the snapshot according to redshift
			Snapshot snap(ss.str());
			snap.load();
			vector<Particle> segment = getSegment(snap, mR, rMin);
			// merge
			mParticles.insert(mParticles.end(), segment.begin(), segment.end());
			rMin = *it;
		} else {
			break;
		}
	}
}

vector<Particle> Lightcone::getSegment(Snapshot& snap, double rMax,
		double rMin) {
	// Check for range correction
	// The lightcone of the middle(origin) observer must not be empty
	// start of the cone must be inside the box
	// translating the rmin point to Cartesian and
	// Calculating the offsets for the original box
	int xOffset, yOffset, zOffset;
	xOffset = calcOffset(rMin * sin(mTheta) * cos(mPhi));
	yOffset = calcOffset(rMin * sin(mTheta) * cos(mPhi));
	zOffset = calcOffset(rMin * cos(mTheta));

	// Define the 8 points that enclose the lightcone in rotated reference frame
	vector<Particle> points;
	double d = rMax * tan(mTheta);
	double dp = rMin * sin(mTheta);
	double rp = rMin * cos(mTheta);
	points.push_back(Particle(-d, -d, rMax));
	points.push_back(Particle(-d, d, rMax));
	points.push_back(Particle(d, -d, rMax));
	points.push_back(Particle(d, d, rMax));
	points.push_back(Particle(-dp, -dp, rp));
	points.push_back(Particle(-dp, dp, rp));
	points.push_back(Particle(dp, -dp, rp));
	points.push_back(Particle(dp, dp, rp));
	reverseRotation(points);
	shiftPointsByObserver(points);
	Box obsBox = makeBoxFromParticles(points);
	Box snapshotBox = Box(BOX_WIDTH * xOffset, BOX_WIDTH * yOffset,
			BOX_WIDTH * zOffset, BOX_WIDTH);

	vector<Particle> inConeTotal;
	// here i, j and k are the observer offsets
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				// Create the collision box for each virutal observers
				Box virtualObsBox = obsBox;
				virtualObsBox.x = virtualObsBox.x + i * BOX_WIDTH;
				virtualObsBox.y = virtualObsBox.y + j * BOX_WIDTH;
				virtualObsBox.z = virtualObsBox.z + k * BOX_WIDTH;
				if (collide(snapshotBox, virtualObsBox)) {
					printf("Collision detected\n");
					// Check lightcone
					vector<Particle> inCone = snap.getCone(rMax, rMin, mTheta,
							mPhi, mOpening, mObserver, xOffset, yOffset,
							zOffset);

					printf("InconeSize: %lu\n", inCone.size());
					// Make corrections
					for (vector<Particle>::iterator it = inCone.begin();
							it != inCone.end(); it++) {
						it->x = it->x - i * BOX_WIDTH;
						it->y = it->y - j * BOX_WIDTH;
						it->z = it->z - k * BOX_WIDTH;
					}
					// Merge two vectors
					inConeTotal.insert(inConeTotal.end(), inCone.begin(),
							inCone.end());
				}
			}
		}
	}
	printf("Segment Size: %lu\n", inConeTotal.size());
	return inConeTotal;
}

void Lightcone::write() {
	stringstream ss;
	ss << "/media/eva/Elements/Lightcone/";
	ss << mR << "." << mTheta << "." << mPhi << "." << mOpening << "." << "csv";

	ofstream file(ss.str().c_str());
	if (file.is_open()) {
		file << "x, y, z, id\n";
		for (vector<Particle>::iterator it = mParticles.begin();
				it != mParticles.end(); it++) {
			file << it->x << ", " << it->y << ", " << it->z << ", " << it->id
					<< "\n";
		}
		printf("[SUCCESS] Write Lightcone to %s\n", ss.str().c_str());
	} else {
		printf("[FAIL] Unable to write to %s\n", ss.str().c_str());
	}

}

// Misc Function

int Lightcone::calcOffset(double pos) {

	if (pos < 0) {
		return (pos / BOX_WIDTH) - 1;
	} else {
		return pos / BOX_WIDTH;
	}

}

bool Lightcone::collide(Box a, Box b) {
	if (a.x + a.w < b.x || b.x + b.w < a.x) {
		return false;
	}
	if (a.y + a.h < b.y || b.y + b.h < b.y) {
		return false;
	}
	if (a.z + a.d < b.z || b.z + b.d < a.z) {
		return false;
	}
	return true;
}

void Lightcone::reverseRotation(vector<Particle>& par) {
	for (vector<Particle>::iterator it = par.begin(); it != par.end(); it++) {
		// rotation around the y-axis, clockwise, by theta
		it->x = it->x * cos(mTheta) + it->z * sin(mTheta);
		it->z = -it->x * sin(mTheta) + it->z * cos(mTheta);
		// rotation around the z axis, clockwise by phi
		it->x = it->x * cos(mPhi) - it->y * sin(mPhi);
		it->y = it->x * sin(mPhi) + it->y * cos(mPhi);
	}
}

Box Lightcone::makeBoxFromParticles(vector<Particle>& par) {
	vector<double> x;
	vector<double> y;
	vector<double> z;
	for (vector<Particle>::iterator it = par.begin(); it != par.end(); it++) {
		x.push_back(it->x);
		y.push_back(it->y);
		z.push_back(it->z);
	}
	Box box;
	box.x = *min_element(x.begin(), x.end());
	box.y = *min_element(y.begin(), y.end());
	box.z = *min_element(z.begin(), z.end());
	box.w = *max_element(x.begin(), x.end()) - box.x;
	box.h = *max_element(y.begin(), y.end()) - box.y;
	box.z = *max_element(z.begin(), z.end()) - box.z;
	return box;
}

void Lightcone::shiftPointsByObserver(vector<Particle>& par) {
	for (vector<Particle>::iterator it = par.begin(); it != par.end(); it++) {
		it->x = it->x + mObserver.x;
		it->y = it->y + mObserver.y;
		it->z = it->z + mObserver.z;
	}
}
