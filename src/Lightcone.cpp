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
	//string redshiftFilePath = "C:\\Users\\user\\Documents\\Lightcones\\redshiftStep.txt";
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
	double rMax = 0;
	for (vector<double>::iterator it = mRedshiftSteps.begin();
			it != mRedshiftSteps.end(); it++, fileIndex++) {
		rMax = *(it + 1) * (1 + *(it + 1)) * 4109.6;
		bool last = false;
		if (rMax > mR) {
			rMax = mR;
			last = true;
		}
		stringstream ss;
		//ss << "C:\\Users\\user\\Documents\\Lightcones\\mini\\" << "tao.";
		ss << "/media/eva/Elements/mini/" << "tao.";
		ss << STARTING_TAO_NUM + fileIndex;
		ss << ".0.csv";
		printf("Loading %d, for z= %f\n", STARTING_TAO_NUM + fileIndex, *it);
		// Load the snapshot according to redshift
		Snapshot snap(ss.str());
		snap.load();
		vector<Particle> segment = getSegment(snap, rMax, rMin);
		// merge
		mParticles.insert(mParticles.end(), segment.begin(), segment.end());
		rMin = rMax;
		if (last) {
			break;
		}
	}
	printf("Lightcone Size: %lu\n", mParticles.size());
}

vector<Particle> Lightcone::getSegment(Snapshot& snap, double rMax,
		double rMin) {
	printf("Generating segment (rMax, rMin) (%.0f, %.0f) \n", rMax, rMin);
	vector<Particle> inSegment;
	// New method
	// First find the master observer collision box

	// Define the 8 points that enclose the lightcone in rotated reference frame
	vector<Particle> points;
	double d = rMax * tan(mOpening);
	// correction to d
	if (d > rMax) {
		d = rMax;
	}
	double dp = rMin * sin(mOpening);
	double rp = rMin * cos(mOpening);
	printf("d:d':r' (%.0f:%.0f:%.0f)\n", d, dp, rp);
	points.push_back(Particle(-d, -d, rMax));
	points.push_back(Particle(-d, d, rMax));
	points.push_back(Particle(d, -d, rMax));
	points.push_back(Particle(d, d, rMax));
	points.push_back(Particle(-dp, -dp, rp));
	points.push_back(Particle(-dp, dp, rp));
	points.push_back(Particle(dp, -dp, rp));
	points.push_back(Particle(dp, dp, rp));
	reverseRotation(points);
	shiftPointsByObserver(points, true);
	Box obsBox = makeBoxFromParticles(points);
	printf(
			"Original Observer box at [%.2f, %.2f, %.2f] with size [%.2f, %.2f, %.2f].\n",
			obsBox.x, obsBox.y, obsBox.z, obsBox.w, obsBox.h, obsBox.d);
	// Calculate the offset range need in each direction
	int xOffMin, xOffMax, yOffMin, yOffMax, zOffMin, zOffMax;
	xOffMin = (obsBox.x / BOX_WIDTH) - 1;
	xOffMax = ((obsBox.x + obsBox.w) / BOX_WIDTH) + 1;
	//printf("x Offset (Min:Max)(%d:%d) \n", xOffMin, xOffMax);

	yOffMin = (obsBox.y / BOX_WIDTH) - 1;
	yOffMax = ((obsBox.y + obsBox.h) / BOX_WIDTH) + 1;
	//printf("y Offset (Min:Max)(%d:%d) \n", yOffMin, yOffMax);

	zOffMin = (obsBox.z / BOX_WIDTH) - 1;
	zOffMax = ((obsBox.z + obsBox.d) / BOX_WIDTH) + 1;
	//printf("z Offset (Min:Max)(%d:%d) \n", zOffMin, zOffMax);

	// Create snapshot boxes from offset and test if they collide with segment
	vector<Particle> validOffsets;
	for (int i = xOffMin; i <= xOffMax; i++) {
		for (int j = yOffMin; j <= yOffMax; j++) {
			for (int k = zOffMin; k <= zOffMax; k++) {
				// Create the box
				Box virtualSnap = Box(i * BOX_WIDTH, j * BOX_WIDTH,
						k * BOX_WIDTH, BOX_WIDTH);
				if (collide(obsBox, virtualSnap)) {
					validOffsets.push_back(Particle(i, j, k));
				}
			}
		}
	}
	printf("%lu boxes are required. \n", validOffsets.size());

	// Check lightcone
	inSegment = snap.getCone(rMax, rMin, mTheta, mPhi, mOpening, mObserver,
			validOffsets);

	//
	//
	//	// Check for range correction
	//	// The lightcone of the middle(origin) observer must not be empty
	//	// start of the cone must be inside the box
	//	// translating the rmin point to Cartesian and
	//	// Calculating the offsets for the original box
	//	int xOffset, yOffset, zOffset;
	//	xOffset = calcOffset(rMin * sin(mTheta) * cos(mPhi));
	//	yOffset = calcOffset(rMin * sin(mTheta) * cos(mPhi));
	//	zOffset = calcOffset(rMin * cos(mTheta));
	//
	//	printf("Offsets (x:y:z) %d:%d:%d\n", xOffset, yOffset, zOffset);
	//
	//	// Define the 8 points that enclose the lightcone in rotated reference frame
	//	vector<Particle> points;
	//	double d = rMax * tan(mOpening);
	//	// correction to d
	//	if (d > rMax) {
	//		d = rMax;
	//	}
	//	double dp = rMin * sin(mOpening);
	//	double rp = rMin * cos(mOpening);
	//	printf("d:d':r' (%.0f:%.0f:%.0f)\n", d, dp, rp);
	//	points.push_back(Particle(-d, -d, rMax));
	//	points.push_back(Particle(-d, d, rMax));
	//	points.push_back(Particle(d, -d, rMax));
	//	points.push_back(Particle(d, d, rMax));
	//	points.push_back(Particle(-dp, -dp, rp));
	//	points.push_back(Particle(-dp, dp, rp));
	//	points.push_back(Particle(dp, -dp, rp));
	//	points.push_back(Particle(dp, dp, rp));
	//	reverseRotation(points);
	//	shiftPointsByObserver(points, true);
	//
	//	Box obsBox = makeBoxFromParticles(points);
	//	printf(
	//			"Original Observer box at [%.2f, %.2f, %.2f] with size [%.2f, %.2f, %.2f].\n",
	//			obsBox.x, obsBox.y, obsBox.z, obsBox.w, obsBox.h, obsBox.d);
	//	Box snapshotBox = Box(BOX_WIDTH * xOffset, BOX_WIDTH * yOffset,
	//			BOX_WIDTH * zOffset, BOX_WIDTH);
	//	printf(
	//			"Snapshot box at [%.2f, %.2f, %.2f] with size [%.2f, %.2f, %.2f].\n",
	//			snapshotBox.x, snapshotBox.y, snapshotBox.z, snapshotBox.w,
	//			snapshotBox.h, snapshotBox.d);
	//
	//	vector<Particle> inConeTotal;
	//	// here i, j and k are the observer offsets
	//	for (int i = -1; i <= 1; i++) {
	//		for (int j = -1; j <= 1; j++) {
	//			for (int k = -1; k <= 1; k++) {
	//				// Create the collision box for each virutal observers
	//				Box virtualObsBox = obsBox;
	//				virtualObsBox.x = virtualObsBox.x + i * BOX_WIDTH;
	//				virtualObsBox.y = virtualObsBox.y + j * BOX_WIDTH;
	//				virtualObsBox.z = virtualObsBox.z + k * BOX_WIDTH;
	//				//if (collide(snapshotBox, virtualObsBox)) {
	//					// Create a virtual observer
	//					Particle virtualObs = mObserver;
	//					// Make corrections
	//					virtualObs.x = virtualObs.x + i * BOX_WIDTH;
	//					virtualObs.y = virtualObs.y + j * BOX_WIDTH;
	//					virtualObs.z = virtualObs.z + k * BOX_WIDTH;
	//					printf("Observer at (%.0f, %.0f, %.0f) has box at ",
	//							virtualObs.x, virtualObs.y, virtualObs.z);
	//
	//					// Output the Virtual Observer Box
	//					printf(
	//							"(%.2f, %.2f, %.2f) with size (%.2f, %.2f, %.2f) collids with the snapshot.\n",
	//							virtualObsBox.x, virtualObsBox.y, virtualObsBox.z,
	//							virtualObsBox.w, virtualObsBox.h, virtualObsBox.d);
	//
	//					// Check lightcone
	//					vector<Particle> inCone = snap.getCone(rMax, rMin, mTheta,
	//							mPhi, mOpening, virtualObs, xOffset, yOffset,
	//							zOffset);
	//
	//					printf("This Observer has lightcone size: %u\n",
	//							inCone.size());
	//					// Make corrections
	//					for (vector<Particle>::iterator it = inCone.begin(); it
	//							!= inCone.end(); it++) {
	//						it->x = it->x - i * BOX_WIDTH;
	//						it->y = it->y - j * BOX_WIDTH;
	//						it->z = it->z - k * BOX_WIDTH;
	//					}
	//
	//					// Error Checking
	//
	//					for (vector<Particle>::iterator it = inCone.begin(); it
	//							!= inCone.end(); it++) {
	//						if (it->x > 500) {
	//							printf("--------------------------\n");
	//							printf("[Error]\n");
	//							printf("[i j k] = [%d %d %d] \n", i, j, k);
	//							printf("--------------------------\n");
	//							break;
	//						}
	//					}
	//					// Merge two vectors
	//					inConeTotal.insert(inConeTotal.end(), inCone.begin(),
	//							inCone.end());
	//				//}
	//			}
	//		}
	//	}

	if (inSegment.size() == 0) {
		printf("[Error] ");
	}
	printf("(rMin:rMax)(%.2f:%.2f) Segment Size: %lu\n", rMin, rMax,
			inSegment.size());
	return inSegment;
}

void Lightcone::write() {
	stringstream ss;
	//ss << "C:\\Users\\user\\Documents\\Lightcones\\generated\\";
	ss << "/media/eva/Elements/generated/";
	ss << setprecision(4) << "(" << mR << ")";
	ss << setprecision(2) << "(" << mTheta / M_PI << ")";
	ss << setprecision(2) << "(" << mPhi / M_PI << ")";
	ss << setprecision(2) << "(" << mOpening / M_PI << ")";
	ss << "." << "csv";

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
	if (a.y + a.h < b.y || b.y + b.h < a.y) {
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
		double tempX = it->x * cos(mTheta) + it->z * sin(mTheta);
		double tempZ = -it->x * sin(mTheta) + it->z * cos(mTheta);
		double tempY = it->y;
		// rotation around the z axis, clockwise by phi
		it->x = tempX * cos(mPhi) - tempY * sin(mPhi);
		it->y = tempX * sin(mPhi) + tempY * cos(mPhi);
		it->z = tempZ;
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
	box.d = *max_element(z.begin(), z.end()) - box.z;
	return box;
}

void Lightcone::shiftPointsByObserver(vector<Particle>& par, bool add = false) {
	int sign = -1;
	if (add) {
		sign = +1;
	}
	for (vector<Particle>::iterator it = par.begin(); it != par.end(); it++) {
		it->x = it->x + sign * mObserver.x;
		it->y = it->y + sign * mObserver.y;
		it->z = it->z + sign * mObserver.z;
	}
}

double Lightcone::getRFromRedshift(double z) {
	return (z) * (1 + z) * 4109.6;
}

// Debug

void Lightcone::dumpParticles(vector<Particle>& par) {
	int id = 0;
	for (vector<Particle>::iterator it = par.begin(); it != par.end();
			it++, id++) {
		printf("id: %d (%.0f:%.0f:%.0f)\n", id, it->x, it->y, it->z);
	}

}

