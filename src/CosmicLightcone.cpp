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
#include "Lightcone.h"
#include "Snapshot.h"

using namespace std;

void printSpacer();
string getStringFromUser(string str);
double getDoubleFromUser(string str, double max, double min);
LightconeSettings getLightconeSettingsFromUser();

bool init();

const static string VERSION_NUMBER = "0.5.0";
const static string PROGRAM_NAME = "Cosmic Lightcone";
const string Snapshot::DIRECTORY_PATH =
		"C:\\Users\\user\\Documents\\Lightcones\\";

int main() {

	Timer runTimer;
	runTimer.start();
	init();

	Lightcone cone;
	cone.loadRedshiftSteps();
	// TO DO: menu stuff here
	cone.setObserver(Particle(1, 1, 1));
	//LightconeSettings ls = getLightconeSettingsFromUser();
	LightconeSettings ls;
	ls.mR = 500;
	ls.mTheta = M_PI / 2;
	ls.mPhi = 0;
	ls.mOpening = 0.25 * M_PI;
	cone.setLightcone(ls);
	cone.generate();
	cone.write();

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

