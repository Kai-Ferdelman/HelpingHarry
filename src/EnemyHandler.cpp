//This is the class that handles the array of enemies

#include "EnemyHandler.hpp"

EnemyHandler::EnemyHandler() {
	//resize and initialize the enemy array
	enemies.resize(ENEMY_NUMBER);
	for (int i = 0; i < ENEMY_NUMBER; i++) {
		enemies[i].setPosition(positions[i]);
	}
}

void EnemyHandler::run(int targetX, int targetY, ofImage enemyImg, Grid* grid, bool inMenu) {
	//calculate the path to the target using the A* search allgorithm
	GridElement* nextTile;
	for (int i = 0; i < ENEMY_NUMBER; i++) {
		if (enemies[i].isActivated && enemies[i].alive) {
			//when an enemy is still alive and activated calculate the shortest path
			try {
				nextTile = grid->aStarSearch(enemies[i].getX(), enemies[i].getY(), targetX, targetY);
				grid->resetSearch();
				//This makes sure that an enemy can't activate through walls
				if (grid->pathLength <= ACTIVATION_DISTANCE) {
					enemies[i].shortPath = true;
				}
				if (enemies[i].shortPath) {
					enemies[i].run(nextTile->getX(), nextTile->getY(), enemyImg, inMenu);
				}
				else {
					enemies[i].display(enemyImg);
				}
			}
			catch (const std::exception&) {}
		}
		//when the enemy is not activated but it is still alive then only draw it but not move it
		else if(enemies[i].alive){
			enemies[i].display(enemyImg);
		}
		enemies[i].activate(targetX, targetY, grid->pathLength);
		enemies[i].time.run();
	}
}