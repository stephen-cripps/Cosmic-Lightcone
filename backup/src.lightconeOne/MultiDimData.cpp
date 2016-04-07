/*
 * MultiDimData.cpp
 *
 *  Created on: 8 Feb 2016
 *      Author: s
 */

#include "MultiDimData.h"

MultiDimData::MultiDimData(int size) :
		mSize(size) {

	// Initialise the 3d vector data

	// Set up sizes
	mData.resize(mSize); // Height
	for (int i = 0; i < mSize; i++) {
		mData[i].resize(mSize);
		for (int j = 0; j < mSize; j++)
			mData[i][j].resize(mSize);
	}

	// Prefill everything with 0
	for (int i = 0; i < mSize; i++) {
		for (int j = 0; j < mSize; j++) {
			for (int k = 0; k < mSize; k++) {
				mData[i][j][k] = 0;
			}
		}
	}

}

double MultiDimData::get(int i, int j, int k) {
	double value = 0;
	if (i >= mSize || j >= mSize || k >= mSize) {
		cout << "Error: MultiDimData: Getting Out of Bound" << endl;
		cout << ", " << i << ":" << j << ":" << k << ". " << endl;
	} else {
		value = mData[i][j][k];
	}
	return value;
}

void MultiDimData::fill(int i, int j, int k, double value) {
	if (i >= mSize || j >= mSize || k >= mSize) {
		cout << "Error: MultiDimData: Filling Out of Bound" << flush;
		cout << ", " << i << ":" << j << ":" << k << ". " << endl;
	} else {
		mData[i][j][k] = value;
	}
}

vector<double> MultiDimData::collapse() {
	vector<double> collapsed;
	for (int i = 0; i < mSize; i++) {
		for (int j = 0; j < mSize; j++) {
			for (int k = 0; k < mSize; k++) {
				collapsed.push_back(mData[i][j][k]);
			}
		}
	}
	return collapsed;
}

bool MultiDimData::writeToFile(string str) {
	bool success = true;
	ofstream outputFile(str.c_str());
	if (outputFile.is_open()) {
		vector<double> array = this->collapse();
		for (vector<double>::iterator it = array.begin(); it != array.end();
				it++) {
			outputFile << *it << "," << endl;
		}
	} else {
		printf("Warning: Failed to write to file! %s \n", str.c_str());
		success = false;
	}
	outputFile.close();
	return success;
}

MultiDimData::~MultiDimData() {
	// TODO Auto-generated destructor stub
}
