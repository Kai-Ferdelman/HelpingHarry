//this is the hpp fil for the enemy handler class

#ifndef EnemyHandler_hpp
#define EnemyHandler_hpp

#include "ofMain.h"
#include "constants.h"
#include "Enemy.hpp"
#include "Grid.hpp"

class EnemyHandler {

public:
	EnemyHandler();
	void run(int, int, ofImage, Grid*, bool);
	std::vector<Enemy> enemies;
	int killCounter = 0;

private:
	ofVec2f positions[ENEMY_NUMBER] = {ofVec2f(22,20), ofVec2f(10,10), ofVec2f(10,20), ofVec2f(15,23), ofVec2f(4,4) };
};

#endif /* EnemyHandler_hpp */