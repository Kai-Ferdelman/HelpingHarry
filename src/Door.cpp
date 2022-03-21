//Knock, knock.
//Who's there?
//Doris.
//Doris who?
//Door is locked that's why I'm knocking! :)

//This class is for the doors that are locked and can be unlocked by being close to them and doing the spell 'Alohomora'. 

#include "Door.hpp"

//This is an empty constructor as two doors are created
Door::Door() {

}

//Constructor, gets passed in a pointer to the grid and the player. Also the font for the text is passed in.
Door::Door(ofVec2f _pos, Grid* _grid, Player* _player, ofTrueTypeFont _typeWriter){
	pos = _pos;
	grid = _grid;
	player = _player;
	typeWriter = _typeWriter;
	for (int i = 0; i < 4; i++) {
		GridElement* doorTile;
		//the surrounding tiles of the door are set to walls
		switch (i) {
		case 0:
			doorTile = &grid->grid[int(pos.x)][int(pos.y)];
			doorTile->setWall(DirectionEast, true);
			std::cout << pos.y << endl;
			
			break;
		case 1:
			doorTile = &grid->grid[int(pos.x)][int(pos.y + 1)];
			doorTile->setWall(DirectionEast, true);
			break;
		case 2:
			doorTile = &grid->grid[int(pos.x + 1)][int(pos.y)];
			doorTile->setWall(DirectionWest, true);
			break;
		case 3:
			doorTile = &grid->grid[int(pos.x + 1)][int(pos.y + 1)];
			doorTile->setWall(DirectionWest, true);
			break;
		}
	}
	destroyed = false;
}

void Door::run(bool paused) {
	//display the door when the game is not paused and the door is not destroyed
	if (!paused && !destroyed) {
		display();
	}
}

void Door::display() {
	//Draw a black rectangle as the door and when the player is close enough to the door display the message
	ofSetColor(30);
	ofRect((pos.x+1)*GRID_ELEMENT_WIDTH - 5, pos.y*GRID_ELEMENT_HEIGHT, 15, GRID_ELEMENT_HEIGHT*2);
	playerPos = ofVec2f(player->getX(), player->getY());
	float dist = pos.distance(playerPos);
	if (dist < DOOR_ACTIVATION) {
		ofSetColor(255);
		typeWriter.drawString("This door is locked!", 400, 917);
	}
}

void Door::Alohomora() {
	//when the spell 'alohomora' is done all the doortiles that were wall are set back to not walls and the door gets destroyed
	playerPos = ofVec2f(player->getX(), player->getY());
	float dist = pos.distance(playerPos);
	if (dist < DOOR_ACTIVATION) {
		for (int i = 0; i < 4; i++) {
			GridElement* doorTile;
			switch (i) {
			case 0:
				doorTile = &grid->grid[int(pos.x)][int(pos.y)];
				doorTile->setWall(DirectionEast, false);
				break;
			case 1:
				doorTile = &grid->grid[int(pos.x)][int(pos.y + 1)];
				doorTile->setWall(DirectionEast, false);
				break;
			case 2:
				doorTile = &grid->grid[int(pos.x + 1)][int(pos.y)];
				doorTile->setWall(DirectionWest, false);
				break;
			case 3:
				doorTile = &grid->grid[int(pos.x + 1)][int(pos.y + 1)];
				doorTile->setWall(DirectionWest, false);
				break;
			}
		}
		destroyed = true;
	}
}