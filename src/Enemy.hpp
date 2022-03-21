//This is the hpp file for a single enemy

#ifndef Enemy_hpp
#define Enemy_hpp

#include "ofMain.h"
#include "constants.h"
#include "Time.hpp"

class Enemy {
public:
	Enemy();
	void run(int, int, ofImage, bool);
	int getX();
	int getY();
	void setPosition(ofVec2f);
	void activate(int, int, int);
	void display(ofImage);

	bool isActivated = false;
	bool shortPath = false;
	bool alive = true;
	Time time;

private:

	void move(int, int);

	float speed;
	float rotation;
	float posX;
	float posY;
};

#endif /* Enemy_hpp */