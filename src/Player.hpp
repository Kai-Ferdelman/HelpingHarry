//this is the hpp file for the player class

#ifndef Player_hpp
#define Player_hpp

#include "ofMain.h"
#include "constants.h"
#include "Enemy.hpp"
#include "Time.hpp"
#include "Grid.hpp"

class Player {
public:
	Player();
	void setTarget(int, int);
	void moveToTarget(int, int);
	void run(ofImage, int, int, std::vector<Enemy> & enemies, bool, Grid*, ofImage);
	void attacked(std::vector<Enemy> & enemies);

	int getX();
	int getY();
	int getTargetX();
	int getTargetY();

	int health = 3;

	float posX, posY;

	bool dead = false;
	bool win = false;

private:
	Time time;

	void display(ofImage);
	void calc();
	void winGame();
	
	bool invincable = false;
	int invincableCounter = 0;

	float targetX, targetY, rotation, speed;

	ofImage stone;
};

#endif /* Player_hpp */