//
//  Grid.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"

#include <algorithm>

#include <cassert>
#include <cmath>

#include "Direction.hpp"
#include "util.hpp"

Grid::Grid() {


  // set positions and neighbours of all elements
  for (int y = 0; y < GRID_SIZE_Y; y++) {
    for (int x = 0; x < GRID_SIZE_X; x++) {
      grid[x][y].setCoordinate(x, y);

      if (x > 0) {
        grid[x][y].setNeighbour(DirectionWest, &grid[x - 1][y]);
      }

      if (x < GRID_SIZE_X - 1) {
        grid[x][y].setNeighbour(DirectionEast, &grid[x + 1][y]);
      }

      if (y > 0) {
        grid[x][y].setNeighbour(DirectionNorth, &grid[x][y - 1]);
      }

      if (y < GRID_SIZE_Y - 1) {
        grid[x][y].setNeighbour(DirectionSouth, &grid[x][y + 1]);
      }
    }
  }
}

void Grid::reset() {
  // reset all elements
  for (int y = 0; y < GRID_SIZE_Y; y++) {
    for (int x = 0; x < GRID_SIZE_X; x++) {
      grid[x][y].reset();
    }
  }
}

void Grid::resetSearch() {
  // reset all elements
  for (int y = 0; y < GRID_SIZE_Y; y++) {
    for (int x = 0; x < GRID_SIZE_X; x++) {
      grid[x][y].resetSearch();
    }
  }
}

void Grid::draw() const {
  // draw all elements
  for (int y = 0; y < GRID_SIZE_Y; y++) {
    for (int x = 0; x < GRID_SIZE_X; x++) {
      grid[x][y].draw();
    }
  }
}

void Grid::clearRect(int first_x, int first_y, int width, int height) {
  int last_x = first_x + width - 1;
  int last_y = first_y + height - 1;

  for (int y = first_y; y <= last_y; y++) {
    for (int x = first_x; x <= last_x; x++) {
      if (x != first_x) {
        grid[x][y].setWall(DirectionWest, false);
      }

      if (x != last_x) {
        grid[x][y].setWall(DirectionEast, false);
      }

      if (y != first_y) {
        grid[x][y].setWall(DirectionNorth, false);
      }

      if (y != last_y) {
        grid[x][y].setWall(DirectionSouth, false);
      }
    }
  }
}

void Grid::drawArc(int x_center, int y_center, int radius, double first_alpha,
                   double last_alpha) {
  assert(first_alpha >= 0.0 && first_alpha <= M_PI * 2);
  assert(last_alpha >= 0.0 && last_alpha <= M_PI * 2);

  for (int y = std::max(0, y_center - radius);
       y <= std::min(y_center + radius, GRID_SIZE_X - 1); y++) {
    for (int x = std::max(0, x_center - radius);
         x <= std::min(x_center + radius, GRID_SIZE_X - 1); x++) {
      int const x_relative = x - x_center;
      int const y_relative = y - y_center;

      double const alpha =
          std::fmod(M_PI * 2 + std::atan2(x_relative, y_relative), M_PI * 2);

      // stop if outside of arc angle range
      if (last_alpha >= first_alpha) {
        if (alpha < first_alpha || alpha > last_alpha) {
          continue;
        }
      } else {
        if (alpha < first_alpha && alpha > last_alpha) {
          continue;
        }
      }

      // stop if outside of arc radius
      if (distance(x_relative, y_relative) >= radius) {
        continue;
      }

      for (int direction = 0; direction < N_DIRECTIONS; direction++) {
        if (grid[x][y].hasNeighbour((Direction)direction)) {
          GridElement* neighbour =
              grid[x][y].getNeighbour((Direction)direction);

          // mark wall if neighbour is outside of arc radius
          int const x_distance = neighbour->getX() - x_center;
          int const y_distance = neighbour->getY() - y_center;

          if (distance(x_distance, y_distance) >= radius) {
            grid[x][y].setWall((Direction)direction, true);
          }
        }
      }
    }
  }
}

GridElement* Grid::getStart() { return &grid[0][0]; }

GridElement* Grid::getEnd() { return &grid[GRID_SIZE_X - 1][GRID_SIZE_Y - 1]; }

