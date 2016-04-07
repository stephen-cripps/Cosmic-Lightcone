//============================================================================
// Name        : CosmicLightcone.cpp
// Author      : Hongbo Tian
// Version     :
// Copyright   : Hongbo Tian 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>		// atof
#include <ctype.h>		// isdigit
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Lightcone.h"
#include "Snapshot.h"

using namespace std;

void printSpacer();
string getStringFromUser(string str);
double getDoubleFromUser(string str, double max, double min);
LightconeSettings getLightconeSettingsFromUser();
string getSnapPath(int sid);

bool init();
bool make(string name);

// Constants
const static string VERSION_NUMBER = "0.8.0";
const static string PROGRAM_NAME = "Cosmic Lightcone";

// Linux
const string Snapshot::DIRECTORY_PATH = "/media/eva/Elements/Snapshot/";
const string Lightcone::REDSHIFT_STEP_PATH =
		"/media/eva/Elements/Snapshot/redshiftStep";
const string Lightcone::OUTPUT_PATH = "/media/eva/Elements/generated/";

// Windows
//const string Snapshot::DIRECTORY_PATH =
//		"C:\\Users\\user\\Documents\\Lightcones\\mini\\";
//const string Lightcone::REDSHIFT_STEP_PATH =
//		"C:\\Users\\user\\Documents\\Lightcones\\redshiftStep.txt";
//const string Lightcone::OUTPUT_PATH =
//		"C:\\Users\\user\\Documents\\Lightcones\\generated\\";

int main() {

	Timer runTimer;
	runTimer.start();
	init();

	Lightcone cone;
	cone.loadRedshiftSteps();
	// TO DO: menu stuff here
	cone.setObserver(Particle(0, 0, 0));
	//LightconeSettings ls = getLightconeSettingsFromUser();
	LightconeSettings ls;
	ls.mR = 50;
	ls.mTheta = M_PI / 2;
	ls.mPhi = M_PI;
	ls.mOpening = 0.1 * M_PI;
	cone.setLightcone(ls);
	cone.generate();
	cone.write();

	cout << "Generation Run time: " << runTimer.getSec() << " Seconds" << endl;
	make("(50)(0.5)(1)(0.1).csv");

	cout << "Total Run time: " << runTimer.getSec() << " Seconds" << endl;
	return 0;
}

bool init() {
	bool success = true;
	printSpacer();
	cout << PROGRAM_NAME << " (Version " << VERSION_NUMBER << ")" << endl;
	cout << "By Hongbo Tian & Stephen Cripps @ The University of Nottingham "
			<< endl;
	printSpacer();
	return success;
}

bool make(string name) {
	bool success = true;
	vector<Particle> particles;
	stringstream iss;
	iss << Lightcone::OUTPUT_PATH;
	iss << name;
	ifstream inputFile(iss.str().c_str());
	if (inputFile.is_open()) {
		string element;
		getline(inputFile, element);
		// Load all the particles
		while (!inputFile.eof()) {
			// Loading all the particles in
			double dValues[3];
			int iValues[2];
			for (int i = 0; i < 3; i++) {
				getline(inputFile, element, ',');
				dValues[i] = atof(element.c_str());
			}
			getline(inputFile, element, ',');
			iValues[0] = atoi(element.c_str());
			getline(inputFile, element, '\n');
			iValues[1] = atoi(element.c_str());
			particles.push_back(
					Particle(dValues[0], dValues[1], dValues[2], iValues[0],
							iValues[1]));
		}
		// Erease the last partciles due to new line
		particles.pop_back();
		inputFile.close();
		printf("[SUCCESS] Make load the lightcone file %lu particles. \n",
				particles.size());
	} else {
		printf("[FAIL] Make unable to read %s\n", iss.str().c_str());
		success = false;
	}

	if (success) {
		stringstream oss;
		oss << Lightcone::OUTPUT_PATH;
		oss << "Catalogue";
		oss << name;
		ofstream outputFile(oss.str().c_str());
		if (outputFile.is_open()) {
			// Continue here
			vector<Particle>::iterator it = particles.begin();

			string mt, mb, rest;
			int sid = 1409;
			int id = -1;
			string line;
			// No error detection here!!!
			ifstream snapFile(getSnapPath(sid).c_str());
			getline(snapFile, line);
			outputFile << line;
			while (it != particles.end()) {
//				printf("it \t %d/%d\n", it->sid, it->id);
//				printf("file \t %d/%d\n", sid, id);
				if (it->sid != sid) {
					// Load the next snapshot
					sid = it->sid;
					snapFile.close();
					snapFile.open(getSnapPath(it->sid).c_str());
					getline(snapFile, line);
					id = -1;
				} else {
					if (it->id != id) {
						while (id != it->id - 1) {
							getline(snapFile, line);
							id++;
						}

						getline(snapFile, mt, ',');
						getline(snapFile, mb, ',');
						getline(snapFile, line, ',');
						getline(snapFile, line, ',');
						getline(snapFile, line, ',');
						getline(snapFile, rest, '\n');
						id++;
					} else {
						outputFile << mt << ", " << mb << ", " << it->x << ", "
								<< it->y << ", " << it->z << "," << rest;
						it++;
					}
				}
			}
		} else {
			printf("[FAIL] Make unable to write to %s\n", iss.str().c_str());
			success = false;
		}
	}
	return success;
}

// -------------- Getters and Misc --------------------

void printSpacer() {
	cout << "  - - - - - - - - - - - - - - - - - - - " << endl;
}

string getStringFromUser(string str) {
	cout << str << endl;
	string rawInput;
	getline(cin, rawInput);
	return rawInput;
}

double getDoubleFromUser(string str, double max = 40000, double min = 0) {
	bool valid = false;
	double value;
	string rawInput;
	while (!valid) {
		printf("Enter %s (min:%.2f max:%.2f) >> ", str.c_str(), min, max);
		getline(cin, rawInput);
		value = atof(rawInput.c_str());
		if (rawInput.size() != 0 && isdigit(rawInput.at(0)) && value >= min
				&& value <= max) {
			valid = true;
		} else {
			printf("The Value(%s) you have entered is invalid!\n",
					rawInput.c_str());
		}
	}
	return value;
}

LightconeSettings getLightconeSettingsFromUser() {
	LightconeSettings lightconeSettings;
	double r, theta, phi, opening;
	r = getDoubleFromUser("Lightcone radius");
	theta = getDoubleFromUser("Lightcone Polar Angle",
			lightconeSettings.THETA_MAX);
	phi = getDoubleFromUser("Lightcone Azimuthal Angle",
			lightconeSettings.PHI_MAX);
	opening = getDoubleFromUser("Lightcone Opening Angle",
			lightconeSettings.OPENING_MAX);
	lightconeSettings.set(r, theta, phi, opening);
	return lightconeSettings;
}

string getSnapPath(int sid) {
	stringstream ss;
	ss << Snapshot::DIRECTORY_PATH;
	ss << "tao.";
	ss << sid;
	ss << ".0.csv";
	return ss.str();
}
