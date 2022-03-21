//This is the hpp file for the door obstacle. It includes the Main, grid, player and constants

#pragma once

#include "ofMain.h"
#include "Grid.hpp"
#include "constants.h"
#include "Player.hpp"

class Door {
public:
	Door();
	Door(ofVec2f, Grid*, Player*, ofTrueTypeFont);
	void run(bool);
	void Alohomora();
	ofVec2f playerPos;
private:
	void display();
	ofVec2f pos;
	Grid* grid;
	Player* player;
	bool destroyed;
	ofTrueTypeFont typeWriter;
};