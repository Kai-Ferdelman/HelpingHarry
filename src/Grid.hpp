//
//  Grid.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "GridElement.hpp"
#include "constants.h"
#include "ofMain.h"

class Grid {
  public:
    Grid();

    void reset();
    void resetSearch();
	int getLength();
    void draw() const;

    // methods for manipulating walls
    void clearRect(int, int, int, int);
    void drawArc(int, int, int, double, double);

    GridElement* getStart();
    GridElement* getEnd();

    void generateRooms(ofImage);

    GridElement* aStarSearch(int, int, int, int);

	int pathLength;

	GridElement grid[GRID_SIZE_X][GRID_SIZE_Y];
    
};

#endif /* Grid_hpp */
