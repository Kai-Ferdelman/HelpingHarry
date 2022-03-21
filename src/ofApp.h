#pragma once

#include "ofMain.h"
#include "Grid.hpp"
#include "Player.hpp"
#include "EnemyHandler.hpp"
#include "UI.hpp"
#include "Time.hpp"
#include "spellDetection.hpp"
#include "Door.hpp"

class ofApp : public ofBaseApp {
 public:
	 ofImage background;
	 ofImage tileMap;
	 ofImage playerWithWand;
	 ofImage imgX;
	 ofImage enemyImage;
	 ofImage heart;
	 ofImage menu;
	 ofImage youWon;
	 ofImage youLost;
	 ofImage spells;
	 ofImage stone;
	 ofImage lumosImage;
	 ofImage alohomoraImage;
	 ofImage avadaKadavraImage;

	 ofTrueTypeFont typeWriter;

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);


  Grid grid;
  Player player;
  Enemy enemy;
  EnemyHandler enemyHandler;
  UI ui;
  spellDetection spellDetector;
  std::vector<Door> doors;
  std::vector<Door*> doorRef;
  Door frontDoor;
  Door backDoor;
};
