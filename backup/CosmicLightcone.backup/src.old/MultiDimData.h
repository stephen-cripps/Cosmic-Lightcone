/*
 * MultiDimData.h
 *
 *  Created on: 8 Feb 2016
 *      Author: s
 */

#ifndef MULTIDIMDATA_H_
#define MULTIDIMDATA_H_

#include <iostream>
#include <vector> 		// Vector for data storage
#include <fstream>		// File stream

using namespace std;

struct MultiDimData {
	MultiDimData(int size);
	virtual ~MultiDimData();

	// Data type dafault to double for now
	// 3D data storage
	int mSize;
	vector<vector<vector<double> > > mData;

	vector<double> collapse();
	bool writeToFile(string str);
	double get(int i, int j, int k); // Extract the elemet at (i,j,k)
	void fill(int i, int j, int k, double value); // Fill the elemet at (i,j,k) with value

};

#endif /* MULTIDIMDATA_H_ */
