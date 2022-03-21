//this is the hpp file for the time class

#pragma once
#include "ofMain.h"

class Time {
private:
	void deltaTimeCalculator();
	int previousTime = 0;
public:
	int deltaTime;
	void run();
};