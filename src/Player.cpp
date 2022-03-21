//this is the class for the player

#include "Player.hpp"


Player::Player() {
	//Set the initial position, target, rotation and speed of the player
	posX = 1;
	posY = GRID_SIZE_Y / 2;
	targetX = 1;
	targetY = int(GRID_SIZE_Y / 2);
	rotation = 0;
	speed = .0035;
}

void Player::run(ofImage playerImg, int _x, int _y, std::vector<Enemy> & enemies, bool inMenu, Grid* grid, ofImage _stone) {
	//calculate the next tile and run all the functions
	stone = _stone;
	if (!inMenu) {
		GridElement* nextTile;
		nextTile = grid->aStarSearch(roundf(posX), roundf(posY), targetX, targetY);
		grid->resetSearch();

		moveToTarget(nextTile->getX(), nextTile->getY());
		display(playerImg);
		attacked(enemies);
		calc();
		winGame();
	}
	time.run();
}

void Player::moveToTarget(int nextStopX, int nextStopY) {
	//move the player to the next tile that was calculated in the run function
	float distX = nextStopX - posX;
	float distY = nextStopY - posY;
	ofVec2f dist = ofVec2f(distX, distY);
	//move and rotate the player to the target until it reaches the target
	if (dist.length() >= 0.3) {
		dist.normalize();
		posX += dist.x * speed * time.deltaTime;
		posY += dist.y * speed * time.deltaTime;
		dist.y *= -1;
		rotation = dist.angle(ofVec2f(0, 1));
	}
}

void Player::display(ofImage playerImg) {
	ofSetColor(255);
	//When the player is in invincalble mode, then change the alpha value of the image
	if (invincable) {
		int alpha = 150+sin(ofGetElapsedTimef()*5)*100;
		ofSetColor(255, 255, 255, alpha);
	}
	//draw the player
	ofPushMatrix();
	ofTranslate(posX * GRID_ELEMENT_WIDTH+GRID_ELEMENT_WIDTH/2, posY * GRID_ELEMENT_HEIGHT+GRID_ELEMENT_HEIGHT/3);
	ofRotate(rotation);
	playerImg.draw(-25, -25, 50, 50);
	ofPopMatrix();
}

void Player::setTarget(int _x, int _y) {
	//set the target od the player
	targetX = _x / GRID_ELEMENT_WIDTH;
	targetY = _y / GRID_ELEMENT_HEIGHT;
}

void Player::attacked(std::vector<Enemy> & enemies) {
	//calculate the distance between the player and the enemy
	ofVec2f playerPosition(posX, posY);
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].alive) {
			ofVec2f enemyPosition(enemies[i].getX(), enemies[i].getY());
			float distance = playerPosition.distance(enemyPosition);
			//when the enemy is on the player, the player still has health and the player is not invincable then the player is attacked
			if (distance < 1 && health > 1 && !invincable) {
				health--;
				invincable = true;
				invincableCounter = 2500;
			}
			//when the player does not have any heath any more then the player is dead
			else if (distance < 1 && !invincable) {
				health--;
				invincable = true;
				invincableCounter = 2500;
				dead = true;
			}
		}
	}
}

void Player::calc() {
	//start counting down the time that the player is invincible
	if (invincableCounter > 0) {
		invincable = true;
		invincableCounter -= time.deltaTime;
	}
	else {
		//when the countdown is below 0 then the player is not invincible anymore
		invincable = false;
	}

}

void Player::winGame() {
	//when the player is at the same position of the object then the player wins
	ofVec2f playerPos(posX, posY);
	ofVec2f objectPos(13, 23);
	int stoneHeight = stone.getHeight();
	int stoneWidth = stone.getWidth();
	stone.resize(stoneWidth / 8, stoneHeight / 8);
	stone.draw(13 * GRID_ELEMENT_WIDTH, 23 * GRID_ELEMENT_HEIGHT);
	if (playerPos.distance(objectPos) < 1) { win = true; }
}

//return rounded position
int Player::getX() { return roundf(posX); }
int Player::getY() { return roundf(posY); }
int Player::getTargetX() { return targetX; }
int Player::getTargetY() { return targetY; }


