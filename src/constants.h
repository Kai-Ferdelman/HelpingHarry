//constants.h

//defines various constants used throughout the classes

#ifndef config_h
#define config_h

#define APP_VERSION_MAJOR 2
#define APP_VERSION_MINOR 1

#define BACKGROUND_WIDTH 1251
#define BACKGROUND_HEIGHT 867

#define WINDOW_WIDTH 1251
#define WINDOW_HEIGHT (BACKGROUND_HEIGHT + 90)

#define GRID_SIZE_X 36
#define GRID_SIZE_Y 26

#define GRID_ELEMENT_WIDTH ((float)BACKGROUND_WIDTH / GRID_SIZE_X)
#define GRID_ELEMENT_HEIGHT ((float)BACKGROUND_HEIGHT / GRID_SIZE_Y)

#define DINING_ROOM_X 290
#define DINING_ROOM_Y 572
#define DINING_ROOM_WIDTH 400
#define DINING_ROOM_HEIGHT 261

#define ENEMY_NUMBER 5

#define ACTIVATION_DISTANCE 4
#define DEACTIVATE_DISTANCE 10
#define DOOR_ACTIVATION 3

#define SPELL_LENGTH 30

#endif /* config_h */
