//
//  GridElement.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//	Edited by Anna van der Linden and Kai Ferdelman
//

#include "GridElement.hpp"

#include <cstdio>

#include "ofMain.h"

#include "constants.h"

GridElement::GridElement() {
  // reset all neighbours
  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    neighbours[direction] = nullptr;
  }

  reset();
}

void GridElement::reset() {
  resetWalls();
  resetSearch();
}

void GridElement::resetWalls() {
  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    walls[direction] = true;
  }
}

void GridElement::resetSearch() {
  visited = false;
  marked = false;
  parent = nullptr;
  path_length = -1;
  distance = -1;
}

void GridElement::draw() const {
  
  // draw all walls
  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    if (walls[direction]) {
      drawWall((Direction)direction);
    }
  }
}

void GridElement::drawWall(Direction direction) const {
  /*ofSetColor(0);

  switch (direction) {
    case DirectionNorth:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionEast:
      ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionSouth:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionWest:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;
  }*/
}

void GridElement::setWall(Direction direction, bool is_solid) {
  walls[direction] = is_solid;

  // set opposite wall if it exists
  if (neighbours[direction] != NULL) {
    neighbours[direction]->walls[oppositeDirection(direction)] = is_solid;
  }
}

bool GridElement::hasWall(Direction direction) const {
  return walls[direction];
}

bool GridElement::wasVisited(Direction direction) const {
  return (neighbours[direction]->visited);
}

int GridElement::getX() const { return x; }

int GridElement::getY() const { return y; }

void GridElement::setCoordinate(int x, int y) {
  this->x = x;
  this->y = y;
}

bool GridElement::hasNeighbour(Direction direction) const {
  return (neighbours[direction] != NULL);
}

GridElement* GridElement::getNeighbour(Direction direction) const {
  return neighbours[direction];
}

void GridElement::setNeighbour(Direction direction, GridElement* newNeighour) {
  neighbours[direction] = newNeighour;
}

int GridElement::manhattanDistance(GridElement const* other) const {
  return (std::abs(x - other->x) + std::abs(y - other->y));
}

void GridElement::visit() { visited = true; }

void GridElement::mark() { marked = true; }

bool GridElement::hasParent() const { return parent != nullptr; }

GridElement* GridElement::getParent() const { return parent; }

void GridElement::setParent(GridElement* parent) { this->parent = parent; }

int GridElement::getPathLength() const { return path_length; }

void GridElement::setPathLength(int path_length) {
  this->path_length = path_length;
}

int GridElement::getDistance() const { return distance; }

void GridElement::setDistance(int distance) { this->distance = distance; }
