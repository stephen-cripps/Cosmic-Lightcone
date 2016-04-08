/*
 * Lightcone.cpp
 *
 *  Created on: 22 Mar 2016
 *      Author: eva
 */

#include "Lightcone.h"

Lightcone::Lightcone() {
	setLightcone(LightconeSettings());
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
	ifstream redShiftFile(REDSHIFT_STEP_PATH.c_str());
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
				REDSHIFT_STEP_PATH.c_str());
	}
	return success;
}

void Lightcone::generate() {
	Timer generationTimer;
	generationTimer.start();

	printf(
			"Generating Lightcone with [R:%.2f, Theta: %.2f, Phi: %.2f, Opening: %.2f]\n",
			mR, mTheta, mPhi, mOpening);
	mParticles.clear();
	int fileIndex = 0;
	double rMin = 0;
	double rMax = 0;
	for (vector<double>::iterator it = mRedshiftSteps.begin();
			it != mRedshiftSteps.end(); it++, fileIndex++) {
		rMax = getRFromRedshift(*(it + 1) / 2);
		bool last = false;
		if (rMax > mR) {
			rMax = mR;
			last = true;
		}
		// Load the snapshot according to redshift
		Snapshot snap(STARTING_TAO_NUM + fileIndex);
		snap.load();
		vector<Particle> segment = getSegment(snap, rMax, rMin);
		// merge
		mParticles.insert(mParticles.end(), segment.begin(), segment.end());
		rMin = rMax;
		if (last) {
			break;
		}
	}
	printf(
			"[COMPLETE] Lightcone generated, %.0f seconds, with %lu particles inside.\n",
			generationTimer.getSec(), mParticles.size());
}

vector<Particle> Lightcone::getSegment(Snapshot& snap, double rMax,
		double rMin) {
	printf("Generating segment (rMax, rMin) (%.0f, %.0f) . . . \n", rMax, rMin);
	vector<Particle> inSegment;
	// First find the observer collision box
	// Define the 8 points that enclose the lightcone in rotated reference frame
	vector<Particle> points;
	double d = rMax * tan(mOpening);
	//	// correction to d
	//	if (d > rMax) {
	//		d = rMax;
	//	}
	double dp = rMin * sin(mOpening);
	double rp = rMin * cos(mOpening);
	//printf("d:d':r' (%.0f:%.0f:%.0f)\n", d, dp, rp);
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

	// Full sky map
	if (mOpening > M_PI / 2) {
		obsBox = Box(mObserver.x - rMax, mObserver.y - rMax, mObserver.z - rMax,
				2 * rMax);
	}

	printf(
			"Original Observer box at [%.2f, %.2f, %.2f] with size [%.2f, %.2f, %.2f], ",
			obsBox.x, obsBox.y, obsBox.z, obsBox.w, obsBox.h, obsBox.d);
	// Calculate the offset range need in each direction
	int xOffMin, xOffMax, yOffMin, yOffMax, zOffMin, zOffMax;
	xOffMin = (obsBox.x / BOX_WIDTH) - 1;
	xOffMax = ((obsBox.x + obsBox.w) / BOX_WIDTH) + 1;
	//	printf("x Offset (Min:Max)(%d:%d) \n", xOffMin, xOffMax);

	yOffMin = (obsBox.y / BOX_WIDTH) - 1;
	yOffMax = ((obsBox.y + obsBox.h) / BOX_WIDTH) + 1;
	//	printf("y Offset (Min:Max)(%d:%d) \n", yOffMin, yOffMax);

	zOffMin = (obsBox.z / BOX_WIDTH) - 1;
	zOffMax = ((obsBox.z + obsBox.d) / BOX_WIDTH) + 1;
	//	printf("z Offset (Min:Max)(%d:%d) \n", zOffMin, zOffMax);

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
	printf("%lu boxes are required.", validOffsets.size());

	// Check lightcone
	inSegment = snap.getCone(rMax, rMin, mTheta, mPhi, mOpening, mObserver,
			validOffsets);

	if (inSegment.size() == 0) {
		printf("[Error] Segment returns 0 particles!\n");
	}
	printf(" Segment Size: %lu\n", inSegment.size());
	return inSegment;
}

void Lightcone::write() {
	stringstream ss;
	ss << OUTPUT_PATH;
	ss << setprecision(4) << "(" << mR << ")";
	ss << setprecision(2) << "(" << mTheta / M_PI << ")";
	ss << setprecision(2) << "(" << mPhi / M_PI << ")";
	ss << setprecision(2) << "(" << mOpening / M_PI << ")";
	ss << "." << "csv";

	ofstream file(ss.str().c_str());
	if (file.is_open()) {
		file << "x, y, z, sid, id\n";
		for (vector<Particle>::iterator it = mParticles.begin();
				it != mParticles.end(); it++) {
			file << it->x << ", " << it->y << ", " << it->z << ", " << it->sid
					<< "," << it->id << "\n";
		}
		printf("[SUCCESS] Saved Lightcone file to %s\n", ss.str().c_str());
	} else {
		printf("[FAIL] Unable to write to %s\n", ss.str().c_str());
	}
}

// Misc Function
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

