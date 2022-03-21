//this is the hpp file of the user interface class

#ifndef UI_hpp
#define UI_hpp

#include "ofMain.h"
#include "constants.h"

class UI {
public:
	void run(ofTrueTypeFont, ofImage, int, ofImage, ofImage, ofImage, ofImage, ofImage, bool, bool, int);
	bool inMenu = true;
	bool lose = false;
	bool win = false;
};

#endif /* UI_hpp */
