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

using namespace std;

int main() {
	/*
	 * This Program reads the snapsoht and delete all galaxies under a supplied mass limit
	 * This assumes the mass of the galaxy is in the first column
	 */
	const static double MASS_LIMIT = 9;

	cout << "- - - Starting Mass Limiter - - -" << endl;

	string inputFilePath = "inputExample";
	string outputFilePath = "outputExample";

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

				// Read the total mass first
				getline(inputFile, input, ',');
				if (atof(input.c_str()) > MASS_LIMIT) {
					// Write to the new file
					outputFile << input << ",";
					getline(inputFile, input, '\n');
					outputFile << input << "\n";
				} else {
					// ignore the to the end of the line
					getline(inputFile, input, '\n');
				}
			}

		} else {
			printf("Error: Unable to open OUTPUT file at %s \n",
					outputFilePath.c_str());
		}
	} else {
		printf("Error: Unable to open INPUT file at %s \n",
				inputFilePath.c_str());
	}

	cout << "- - - End of Mass Limiter - - -" << endl;
	return 0;
}
