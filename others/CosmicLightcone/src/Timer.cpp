/*
 * Timer.cpp
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#include "Timer.h"

Timer::Timer() :
		mStartTicks(0), mPausedTicks(0), mStarted(false), mPaused(false) {
}

void Timer::start() {
	// This also works as a restart
	mStarted = true;
	mPaused = false;

	mStartTicks = (int) clock();
	mPausedTicks = 0;

}

void Timer::stop() {
	mStarted = false;
	mPaused = false;

}

void Timer::pause() {
	if (mStarted && !mPaused) {
		mPaused = true;
		mPausedTicks = (int) clock() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unPause() {
	if (mStarted && mPaused) {
		mPaused = false;
		mStartTicks = (int) clock() - mPausedTicks;
		mPausedTicks = 0;
	}
}

int Timer::getTicks() {
	int time = 0;
	if (mStarted) {
		if (mPaused) {
			time = mPausedTicks;
		} else {
			time = (int) clock() - mStartTicks;
		}
	}
	return time;
}

double Timer::getSec() {
	return (double) getTicks() / CLOCKS_PER_SEC;
}

// Getters
bool Timer::isStarted() {
//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused() {
//Timer is running and paused
	return mPaused && mStarted;
}

