//this is the hpp file of the spell detection class

#pragma once

#include "ofMain.h"
#include "constants.h"
#include "ofxOpenCv.h"			//library for camera access and image manipulation
#include "Door.hpp"
#include "EnemyHandler.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Time.hpp"

class spellDetection {
public:
	spellDetection();
	spellDetection(std::vector<Door*>, EnemyHandler*, Player*, ofImage, ofImage, ofImage);
	void run(bool);
	void getPixelColor(ofVec2f);
	bool inConfigurationMode = true;

private:
	void getImage();
	void tracker();
	void spell();
	void draw(bool);
	void lumosSpell();

	int resolution = 16;
	int spellCounter = 0;

	bool lumos = false;
	bool alohomora = false;
	bool avadaKadavra = false;

	std::vector<Door*> doors;
	EnemyHandler* enemyHandler;
	Player* player;
	Time time;

	ofVideoGrabber vidGrabber;
	ofxCvColorImage inputImg;
	ofxCvColorImage outputImg;
	ofImage darknessIn;
	ofImage darknessOut;
	ofImage lumosImage;
	ofImage alohomoraImage;
	ofImage avadaKadavraImage;
	ofColor thresholdColor;
	ofVec2f pos[30];
	ofVec2f center;
};