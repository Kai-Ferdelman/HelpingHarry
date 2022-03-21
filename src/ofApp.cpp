#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

  //Load all the images that are used and resize some of them
  std::srand((unsigned int)std::time(0));
  background.load("images/background_v_kai.png");
  tileMap.load("images/tileMap.png");
  playerWithWand.load("images/playerWithWand.png");
  imgX.load("images/X.png");
  enemyImage.load("images/enemy.png");
  heart.load("images/heart.png");
  menu.load("images/menu.PNG");
  youWon.load("images/youWon.PNG");
  youLost.load("images/youLost.PNG");
  spells.load("images/spells.png");
  stone.load("images/stone.png");
  lumosImage.load("images/lumosImage.png");
  alohomoraImage.load("images/alohomoraImage.png");
  avadaKadavraImage.load("images/avadaKadavraImage.png");
  spells.resize(200, WINDOW_HEIGHT - BACKGROUND_HEIGHT);
  lumosImage.resize(56, 600);
  alohomoraImage.resize(600, 600);
  avadaKadavraImage.resize(400, 600);
  //load the font
  typeWriter.load("special-elite/SpecialElite.ttf", 30);
  //create a grid with walls
  grid.generateRooms(tileMap);
  //set the amount of doors and their position
  doors.resize(2);
  doors[0] = Door(ofVec2f(7, 15), &grid, &player, typeWriter);
  doors[1] = Door(ofVec2f(29, 9), &grid, &player, typeWriter);
  //create an array of references to the doors
  doorRef.resize(2);
  for (int i = 0; i < doors.size(); i++) {
	  doorRef[i] = &doors[i];
  }

  spellDetector = spellDetection(doorRef, &enemyHandler, &player, lumosImage, alohomoraImage, avadaKadavraImage);
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
	//draw the background image and the grid 
	ofBackground(0);
	ofSetColor(255);
	background.draw(0, 0);
	grid.draw();
	imgX.draw(player.getTargetX()*GRID_ELEMENT_WIDTH, player.getTargetY()*GRID_ELEMENT_HEIGHT, 30, 30);
	//the game is nout paused unless the menu, configuration or one of the end screens is displayed
	bool paused = false;
	if (ui.inMenu || spellDetector.inConfigurationMode || ui.lose || ui.win) { paused = true; }
	try {
		//run the player and the enemies
		player.run(playerWithWand, 0, 0, enemyHandler.enemies, paused, &grid, stone);
		enemyHandler.run(player.getX(), player.getY(), enemyImage, &grid, paused);
	}
	catch (const std::exception&) {}
	//run the user interface
	ui.run(typeWriter, heart, player.health, background, menu, youWon, youLost, spells, player.win, player.dead, enemyHandler.killCounter);
	//run the doors
	for (Door door : doors) {
		door.run(paused);
	}
	//run the class that detects the spell
	spellDetector.run(paused);
	ofSetColor(255);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//when key 13 (enter) is pressed the menu is toggled
	if (key == 13) {
		ui.inMenu = !ui.inMenu;
	}
	//when key c is pressed go into configuration mode
	if (key == 'c') {
		spellDetector.inConfigurationMode = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//when the mouse is pressed set the player target to that position
	if (!ui.inMenu && !spellDetector.inConfigurationMode) {
		player.setTarget(x, y);
	}
	//when in configuration mode the position of the mouse sets the color for the tracking
	if (spellDetector.inConfigurationMode) {
		spellDetector.getPixelColor(ofVec2f(x,y));
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
