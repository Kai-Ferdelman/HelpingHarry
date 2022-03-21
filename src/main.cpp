#include "ofApp.h"
#include "ofMain.h"

#include "constants.h"

//========================================================================
int main() {
  std::cout << "Helping Harry v" << APP_VERSION_MAJOR << '.'
            << APP_VERSION_MINOR << '\n';
  ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);
  ofRunApp(new ofApp());
}
