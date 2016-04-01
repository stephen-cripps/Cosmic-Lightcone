/*
 * Timer.h
 *
 *  Created on: 6 Feb 2016
 *      Author: eva
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>	// System Time

class Timer {
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unPause();

	// Get Timer Ticks
	int getTicks();
	double getSec();

	// Getters
	bool isStarted();
	bool isPaused();
private:
	int mStartTicks, mPausedTicks;

	bool mStarted, mPaused;
};

#endif /* TIMER_H_ */
