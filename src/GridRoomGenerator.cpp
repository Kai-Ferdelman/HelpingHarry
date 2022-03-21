// this is the class that generates the walls according to the color map image

#include "Grid.hpp"
#include "ofMain.h"
#define _USE_MATH_DEFINES
#include <cmath>



void Grid::generateRooms(ofImage background) {
  // clear the map
  clearRect(0, 0, GRID_SIZE_X, GRID_SIZE_Y);
  for (int i = 0; i < background.getWidth(); i++) {
	  for (int j = 0; j < background.getHeight(); j++) {
		  //Get the r,g,b value of every pixel in the color map
		  ofColor tileColor = background.getColor(i, j);
		  int red = tileColor.r;
		  int blue = tileColor.b;
		  int green = tileColor.g;

		  //when a tile is black, then set walls on all sides
		  if (red == 0 && green == 0 && blue == 0) {
			grid[i][j].setWall(DirectionNorth, true);
			grid[i][j].setWall(DirectionEast, true);
			grid[i][j].setWall(DirectionSouth, true);
			grid[i][j].setWall(DirectionWest, true);
		  }
		  //for every specific red value of the tile set the wall(s) according to that red value
		  else if(red != 255 && green != 255 && blue != 255){
			  switch (red)
			  {
			  case 255:
				  grid[i][j].setWall(DirectionEast, true);
				  break;
			  case 245:
				  grid[i][j].setWall(DirectionWest, true);
				  break;
			  case 235:
				  grid[i][j].setWall(DirectionNorth, true);
				  break;
			  case 225:
				  grid[i][j].setWall(DirectionSouth, true);
				  break;
			  case 215:
				  grid[i][j].setWall(DirectionWest, true);
				  grid[i][j].setWall(DirectionNorth, true);
				  break;
			  case 205:
				  grid[i][j].setWall(DirectionEast, true);
				  grid[i][j].setWall(DirectionNorth, true);
				  break;
			  case 195:
				  grid[i][j].setWall(DirectionWest, true);
				  grid[i][j].setWall(DirectionSouth, true);
				  break;
			  case 185:
				  grid[i][j].setWall(DirectionEast, true);
				  grid[i][j].setWall(DirectionSouth, true);
				  break;
			  case 175:
				  grid[i][j].setWall(DirectionNorth, true);
				  grid[i][j].setWall(DirectionSouth, true);
				  break;
			  case 165:
				  grid[i][j].setWall(DirectionEast, true);
				  grid[i][j].setWall(DirectionWest, true);
				  break;
			  default:
				  //no Walls
				  break;
			  }
		  }
	  }
  }
}
