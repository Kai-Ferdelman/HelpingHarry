//this is the class for the user interface

#include "UI.hpp"

void UI::run(ofTrueTypeFont typeWriter, ofImage _heart, int playerHealth, ofImage _background, ofImage _menu, ofImage _youWon, ofImage _youLost, ofImage _spells, bool _win, bool _lose, int _killCount) {
	//takes care of all the menu screens and the background
	ofSetColor(255);
	win = _win;
	lose = _lose;
	//draw menu screen
	if (inMenu) {
		_menu.draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	//draw lose screen
	else if (lose) {
		ofSetColor(255);
		_youLost.draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		string kills = std::to_string(_killCount);
		typeWriter.drawString(kills, 710, 715);
	}
	//draw win screen
	else if (win) {
		_youWon.draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		string kills = std::to_string(_killCount);
		typeWriter.drawString(kills, 710, 715);
	}
	//draw the hearts of the players health and the spell key
	else {
		for (int i = 0; i < playerHealth; i++) {
			_heart.draw(20 + i * 70, BACKGROUND_HEIGHT + 20, 50, 50);
		}
		_spells.draw(BACKGROUND_WIDTH - 220, BACKGROUND_HEIGHT);
	}


}
