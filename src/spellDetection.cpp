//this is the class that handles the tracking of the color and detects the spells

#include "spellDetection.hpp"

spellDetection::spellDetection() {}

spellDetection::spellDetection(std::vector <Door*> _doors, EnemyHandler* _enemyHandler, Player* _player, ofImage _lumosImage, ofImage _alohomoraImage, ofImage _avadaKadavraImage) {
	//initializes objects
	doors = _doors;
	enemyHandler = _enemyHandler;
	player = _player;
	lumosImage = _lumosImage;
	alohomoraImage = _alohomoraImage;
	avadaKadavraImage = _avadaKadavraImage;
	vidGrabber.setVerbose(true);
	vidGrabber.setup(160, 120);
	inputImg.allocate(160, 120);
	outputImg.allocate(160, 120);
	for (ofVec2f position : pos) {
		position = ofVec2f(0, 0);
	}
	darknessIn.allocate(DINING_ROOM_WIDTH / resolution, DINING_ROOM_HEIGHT / resolution, OF_IMAGE_COLOR_ALPHA);
	darknessOut.allocate(DINING_ROOM_WIDTH / resolution, DINING_ROOM_HEIGHT / resolution, OF_IMAGE_COLOR_ALPHA);
}

void spellDetection::run(bool _paused) {
	getImage();
	draw(_paused);
	time.run();
}

void spellDetection::draw(bool _paused) {
	//in config mode draw camera image
	ofSetColor(255);
	if (inConfigurationMode) {
		inputImg.draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	//in game draw a circle at the tracked position
	else  if(!_paused){
		ofSetColor(150, 50);

		int x = WINDOW_WIDTH - (center.x / inputImg.width * WINDOW_WIDTH);
		int y = center.y / inputImg.height * WINDOW_HEIGHT;
		if (x != 0 && y != 0) {
			ofEllipse(x, y, 100, 100);

		}
		lumosSpell();
	}
	//for a short time display the spell as an image on the screen
	if (spellCounter > 0) {
		spellCounter -= time.deltaTime;
		ofSetColor(255, spellCounter / 4);
		if (lumos) {
			lumosImage.draw(600, 100);
		}
		else if (alohomora) {
			alohomoraImage.draw(350, 100);
		}
		else if (avadaKadavra) {
			avadaKadavraImage.draw(350, 100);
		}
	}
}

void spellDetection::getImage() {
	//access webcam and take image
	vidGrabber.update();
	inputImg.setFromPixels(vidGrabber.getPixels());
	outputImg = inputImg;
	tracker();
}

void spellDetection::tracker() {
	//find pixels that match the object color
	int xAverage = 0;
	int yAverage = 0;
	int points = 0;
	for (int x = 0; x < outputImg.width; x++) {
		for (int y = 0; y < outputImg.height; y++) {
			ofColor rgbColor = outputImg.getPixels().getColor(x, y);
			if ((rgbColor.getHue() > thresholdColor.getHue() - 10 && rgbColor.getHue() < thresholdColor.getHue() + 10) && rgbColor.getSaturation() > thresholdColor.getSaturation() - 10 && rgbColor.getBrightness() > thresholdColor.getBrightness() - 10 /*rgbColor.getLightness() > 250*/) {
				points++;
				xAverage += x;
				yAverage += y;
			}
		}
	}
	//find the center position of the object
	if (points != 0) {
		xAverage /= points;
		yAverage /= points;
	}
	//ignore random pixels with the same color
	if (points < 20) {
		spell();
		center.x = 0;
		center.y = 0;
		for (int i = 0; i < SPELL_LENGTH - 1; i++) {
			pos[i] = ofVec2f(0, 0);
		}
	}
	//save last 30 frames into position array
	else {
		center.x = xAverage;
		center.y = yAverage;
		pos[SPELL_LENGTH - 1] = center;

		for (int i = 0; i < SPELL_LENGTH - 1; i++) {
			pos[i] = pos[i + 1];
		}
	}
}

void spellDetection::getPixelColor(ofVec2f mousePosition) {
	//set object color to the pixel color that is clicked in config mode
	ofColor pixelColor(0, 0, 0);
	try {
		int x = mousePosition.x / WINDOW_WIDTH * inputImg.width;
		int y = mousePosition.y / WINDOW_HEIGHT * inputImg.height;
		thresholdColor = inputImg.getPixels().getColor(x, y);
		inConfigurationMode = false;
	}
	catch (exception e) {}
}

void spellDetection::spell() {
	//check if a new spell has been cast
	bool spellCast = false;
	for (int i = 0; i < SPELL_LENGTH - 1; i++) {
		if (pos[i].x != 0 && pos[i].y != 0) {
			spellCast = true;
			break;
		}
	}
	//if spell is shorter than 30 frames, grab the first position
	int firstPos = 0;
	for (int i = SPELL_LENGTH; i > 0; i--) {
		if (pos[i].x == 0 && pos[i].y == 0) {
			firstPos = i + 1;
			break;
		}
	}
	if (spellCast) {

		//Alohomora
		//checks if the spell is alohomora by going through each quartile of the screen
		int quartileCounter = 0;
		for (int i = 0; i < SPELL_LENGTH; i++) {
			if (quartileCounter == 0 && pos[i].x < inputImg.width / 2 && pos[i].y < inputImg.height / 2) {
				quartileCounter++;
			}
			else if (quartileCounter == 1 && pos[i].x < inputImg.width / 2 && pos[i].y > inputImg.height / 2) {
				quartileCounter++;
			}
			else if (quartileCounter == 2 && pos[i].x > inputImg.width / 2 && pos[i].y > inputImg.height / 2) {
				quartileCounter++;
			}
			else if (quartileCounter == 3 && pos[i].x > inputImg.width / 2 && pos[i].y < inputImg.height / 2) {
				quartileCounter++;
				break;
			}
		}
		if (quartileCounter == 4) {
			//start the counter for displaying the spell
			alohomora = true;
			lumos = false;
			avadaKadavra = false;
			spellCounter = 1000;

			//open the door that the player is close to
			for (Door* door : doors) {
				door->Alohomora();
			}
		}

		//Avada Kadavra
		//checks if the spell is avada kadavra by checking if it starts in the right upper corner and ends in the left down corner
		else if (pos[firstPos + 1].x < inputImg.width / 2 && pos[firstPos + 1].y < inputImg.height / 2 && pos[SPELL_LENGTH - 1].x > inputImg.width / 2 && pos[SPELL_LENGTH - 1].y > inputImg.height / 2) {
			avadaKadavra = true;
			alohomora = false;
			lumos = false;
			//start the counter
			spellCounter = 1000;
			//get the size of the enemies array and kill the enemies that are in the actuvation distance
			int enemyArraySize = enemyHandler->enemies.size();
			ofVec2f playerPos(player->getX(), player->getY());
			for (int i = 0; i < enemyArraySize; i++) {
				ofVec2f enemyPos(enemyHandler->enemies[i].getX(), enemyHandler->enemies[i].getY());
				float dist = playerPos.distance(enemyPos);
				if (dist < ACTIVATION_DISTANCE+1) {
					enemyHandler->enemies[i].alive = false;
					enemyHandler->killCounter++;
					break;
				}
			}
		}

		//Lumos
		//check if the spell starts in the middle part of the screen and goes straight down
		else if (pos[firstPos + 1].y < inputImg.height / 2 && pos[SPELL_LENGTH - 1].y > inputImg.height / 2) {
			int x = pos[firstPos + 1].x;
			if (pos[SPELL_LENGTH - 1].x > x - inputImg.width / 6 && pos[SPELL_LENGTH - 1].x < x + inputImg.width / 6) {
				lumos = !lumos;
				alohomora = false;
				avadaKadavra = false;
				spellCounter = 1000;
			}
		}

	}
}

void spellDetection::lumosSpell() {
	//takes care of the flashlight effect when the lumos spell is done
	if (!lumos) {
		ofSetColor(0);
		ofRect(DINING_ROOM_X, DINING_ROOM_Y, DINING_ROOM_WIDTH, DINING_ROOM_HEIGHT);
	}
	//calculate distance between the player and the pixel
	else {
		ofVec2f playerPos((player->posX*GRID_ELEMENT_WIDTH - DINING_ROOM_X)/resolution, (player->posY*GRID_ELEMENT_HEIGHT - DINING_ROOM_Y)/resolution);
		for (int x = 0; x < darknessIn.getWidth(); x++) {
			for (int y = 0; y < darknessIn.getHeight(); y++) {
				ofVec2f pixPos(x, y);
				float dist = pixPos.distance(playerPos) *resolution * 1.5f;
				if (dist < 256) {
					darknessIn.getPixels().setColor(x, y, ofColor(0, dist));
				}
				else {
					darknessIn.getPixels().setColor(x, y, ofColor(0));
				}
			}
		}
		ofSetColor(255);
		darknessOut = darknessIn;
		darknessOut.draw(DINING_ROOM_X, DINING_ROOM_Y, DINING_ROOM_WIDTH, DINING_ROOM_HEIGHT);
	}
}
