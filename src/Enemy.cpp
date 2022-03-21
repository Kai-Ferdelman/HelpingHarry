//This is the class for a single enemy

#include "Enemy.hpp"

Enemy::Enemy() {
	//an enemy gets a random speed
	speed = ofRandom(15, 23) / 10000;
	rotation = 0;
}

void Enemy::run(int targetX, int targetY, ofImage enemyImage, bool inMenu){
	//when the game is not in the menu, run the display and run function
	if (!inMenu) {
		display(enemyImage);
		move(targetX, targetY);
	}
}
void Enemy::display(ofImage enemyImage){
	//Draw the enemy and rotate it
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(posX * GRID_ELEMENT_WIDTH + GRID_ELEMENT_WIDTH / 2, posY * GRID_ELEMENT_HEIGHT + GRID_ELEMENT_HEIGHT / 3);
	ofRotate(rotation);
	enemyImage.draw(-25, -25, 50, 50);
	ofPopMatrix();
}
void Enemy::move(int targetX, int targetY) {
	//The enemy gets the target position from the player and calculate the distance to the target, then move the enemy to the target
	float distX = targetX - posX;
	float distY = targetY - posY;
	ofVec2f dist = ofVec2f(distX, distY);
	if (dist.length() >= 0.1) {
		//normalize the vector so the speed doesn't get incredably high
		dist.normalize();
		//Move the enemy to the target and rotate it
		posX += dist.x * speed * time.deltaTime;
		posY += dist.y * speed * time.deltaTime;
		dist.y *= -1;
		rotation = dist.angle(ofVec2f(0, 1));
	}
}
void Enemy::activate(int _x, int _y, int _pathLength) {
	//calculate the distance between the position of the player and the position of the enemy
	ofVec2f enemyPosition(posX, posY);
	ofVec2f playerPosition(_x, _y);
	float distance = enemyPosition.distance(playerPosition);
	//When the player is close enough to the enemy, activate the enemy
	if (distance < ACTIVATION_DISTANCE) {
		isActivated = true;
	}
	//When the player is too far away from the enemy, deactivate the enemy
	else if (distance > DEACTIVATE_DISTANCE) {
		isActivated = false;
		shortPath = false;
	}

}

//Retuns rounded position
int Enemy::getX() { return roundf(posX); }
int Enemy::getY() { return roundf(posY); }
void Enemy::setPosition(ofVec2f pos) { posX = pos.x; posY = pos.y; }