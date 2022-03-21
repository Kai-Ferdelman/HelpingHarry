//this is the class for the time

#include "Time.hpp"

void Time::run() {
	deltaTimeCalculator();
}

void Time::deltaTimeCalculator() {
	//gets the time in milliseconds that have passed since the last frame
	deltaTime = 0;
	int newTime = ofGetElapsedTimeMillis();
	deltaTime = newTime - previousTime;
	if (deltaTime < 0 || deltaTime > 1000) { deltaTime = 0;}
	previousTime = newTime;
}