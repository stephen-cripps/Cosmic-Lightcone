//============================================================================
// Name        : SnapShotMassLimiter.cpp
// Author      : Hongbo Tian
// Version     :
// Copyright   : Hongbo Tian 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>		// File Stream
#include <stdlib.h>		// atof
#include <sstream> 		// string stream
using namespace std;

int main() {
	/*
	 * This Program reads the snapsoht and delete all galaxies under a supplied mass limit
	 * This assumes the mass of the galaxy is in the first column
	 */
	const static double MASS_LIMIT = 0.1;

	cout << "- - - Creating Mini Snapshots - - -" << endl;

	for (int id = 1409; id <= 1433; id++) {

		// Formating file path
		stringstream inputSS, outputSS;
		inputSS << "C:\\Users\\user\\Documents\\Lightcones\\tao." << id
				<< ".0.csv";
		outputSS << "C:\\Users\\user\\Documents\\Lightcones\\mini\\tao." << id
				<< ".0.csv";

		string inputFilePath = inputSS.str();
		string outputFilePath = outputSS.str();

		int readCount, writeCount;
		readCount = writeCount = 0;

		// Opening the input File
		ifstream inputFile(inputFilePath.c_str());
		if (inputFile.is_open()) {
			// Input file is successfully opened
			// Prepare the output file
			ofstream outputFile(outputFilePath.c_str());
			if (outputFile.is_open()) {
				// First we read the headings and write it to file
				string input;
				getline(inputFile, input);
				outputFile << input << endl;

				// Main Checking function
				while (!inputFile.eof()) {
					// Write every 100th line
					for (int i = 0; i < 100; i++) {
						getline(inputFile, input);
						readCount++;
					}
					outputFile << input << endl;
					writeCount++;
				}

			} else {
				printf("Error: Unable to open OUTPUT file at %s \n",
						outputFilePath.c_str());
			}
		} else {
			printf("Error: Unable to open INPUT file at %s \n",
					inputFilePath.c_str());
		}

		printf("(%d/%d) Galaxies Read: %d, Galaxies Wrote: %d \n", id, 1433,
				readCount, writeCount);
	}

	cout << "- - - End of Mini Snapshot Creator - - -" << endl;
	return 0;
}
