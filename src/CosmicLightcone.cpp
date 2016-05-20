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
#include <fstream>		// File stream
#include "Lightcone.h"
#include "Snapshot.h"

using namespace std;

void printSpacer();
string getStringFromUser(string str);
double getDoubleFromUser(string str, double max, double min);
LightconeSettings getLightconeSettingsFromUser();
Particle getObserverPositionFromUser();
string getSnapPath(int sid);

bool init();
bool loadSettings();
bool makeNow(vector<Particle> particles, LightconeSettings settings,
		Particle obs);

// Constants
const static string VERSION_NUMBER = "0.8.2";
const static string PROGRAM_NAME = "Cosmic Lightcone";

// Linux
string Snapshot::DIRECTORY_PATH = "";
string Lightcone::REDSHIFT_PATH = "";
string Lightcone::OUTPUT_PATH = "";
int Lightcone::TAO_STARTING_ID = 0;

int main() {

	Timer runTimer;
	runTimer.start();
	init();

	LightconeSettings coneSettings = getLightconeSettingsFromUser();
	Lightcone cone;
	cone.loadRedshiftSteps();
	Particle obs = getObserverPositionFromUser();
	cone.setObserver(obs);
	cone.setLightcone(coneSettings);
	cone.generate();
	cone.write();
	cout << "Generation Run time: " << runTimer.getSec() << " Seconds" << endl;
	printSpacer();
	makeNow(cone.mParticles, coneSettings, obs);
	printSpacer();
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

	cout << "Loading System Settings . . . " << endl;
	success = loadSettings();
	return success;
}

bool loadSettings() {
	bool success = true;
	ifstream settingsFile("settings");
	// No Error detection here
	bool TestMode = false;

	if (settingsFile.is_open()) {
		printSpacer();
		string input;
		// Test Mode
		getline(settingsFile, input, '=');
		getline(settingsFile, input, '\n');
		if (input == "TRUE") {
			TestMode = true;
			cout << "Program is in TEST MODE." << endl;
		}
		// Tao starting ID
		getline(settingsFile, input, '=');
		getline(settingsFile, input, '\n');
		Lightcone::TAO_STARTING_ID = atoi(input.c_str());
		cout << "SET TAO staring ID: " << Lightcone::TAO_STARTING_ID << endl;
		// Redshift
		getline(settingsFile, input, '=');
		getline(settingsFile, input, '\n');
		Lightcone::REDSHIFT_PATH = input;
		cout << "Set Redshift: " << input.c_str() << endl;
		// Snapshots
		if (TestMode) {
			getline(settingsFile, input, '\n');
		}
		getline(settingsFile, input, '=');
		getline(settingsFile, input, '\n');
		Snapshot::DIRECTORY_PATH = input;
		cout << "SET Snapshots: " << input.c_str() << endl;
		if (!TestMode) {
			getline(settingsFile, input, '\n');
		}
		// Output
		getline(settingsFile, input, '=');
		getline(settingsFile, input, '\n');
		Lightcone::OUTPUT_PATH = input;
		cout << "SET Output: " << input.c_str() << endl;
		printSpacer();
	} else {
		printf("[FAIL] Unable to reading settings.\n");
		success = false;
	}

	return success;
}

bool makeNow(vector<Particle> particles, LightconeSettings settings,
		Particle obs) {
	bool success = true;

	stringstream oss;
	oss << Lightcone::OUTPUT_PATH;
	oss << "MOCK";
	oss << "(" << obs.x << "," << obs.y << "," << obs.z << ")";
	oss << "(" << settings.mR << ")";
	oss << "(" << 180 * settings.mTheta / M_PI << ")";
	oss << "(" << 180 * settings.mPhi / M_PI << ")";
	oss << "(" << 180 * settings.mHO / M_PI << ")";
	oss << ".csv";
	ofstream outputFile(oss.str().c_str());
	if (outputFile.is_open()) {
		// Continue here
		vector<Particle>::iterator it = particles.begin();

		string mt, rest;
		int sid = 2000;
		int id = -1;
		string line;
		// No error detection here!!!
		ifstream snapFile(getSnapPath(sid).c_str());
		getline(snapFile, line);
		outputFile << line << "\n";
		while (it != particles.end()) {
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
					getline(snapFile, line, ',');
					getline(snapFile, line, ',');
					getline(snapFile, line, ',');
					getline(snapFile, rest, '\n');
					id++;
				} else {
					outputFile << mt << ", " << it->x << ", " << it->y << ", "
							<< it->z << "," << rest << "\n";
					it++;
				}
			}
		}
	} else {
		printf("[FAIL] Make unable to write to %s\n", oss.str().c_str());
		success = false;
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

double getDoubleFromUser(string str, double min, double max) {
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
	printSpacer();
	LightconeSettings lightconeSettings;
	double r, theta, phi, opening;
	r = getDoubleFromUser("Lightcone radius", 0, 80000);
	theta = M_PI * getDoubleFromUser("Lightcone Polar Angle [Degrees]", 0, 360)
			/ 180;
	phi = M_PI * getDoubleFromUser("Lightcone Azimuthal Angle [Degrees]", 0,
			180) / 180;
	opening = M_PI * getDoubleFromUser(
			"Lightcone Half Opening Angle [Degrees]", 0, 180) / 180;
	lightconeSettings.set(r, theta, phi, opening);
	printSpacer();
	return lightconeSettings;
}

Particle getObserverPositionFromUser() {
	Particle obs;
	printSpacer();
	obs.x = getDoubleFromUser("Observer X Position", 0, 500);
	obs.y = getDoubleFromUser("Observer Y Position", 0, 500);
	obs.z = getDoubleFromUser("Observer Z Position", 0, 500);
	printSpacer();
	return obs;
}

string getSnapPath(int sid) {
	stringstream ss;
	ss << Snapshot::DIRECTORY_PATH;
	ss << "tao.";
	ss << sid;
	ss << ".0.csv";
	return ss.str();
}
