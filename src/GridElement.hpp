//
//  GridElement.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef GridElement_hpp
#define GridElement_hpp

#include "Direction.hpp"

class GridElement {
 public:
  GridElement();

  void reset();
  void resetWalls();
  void resetSearch();

  void draw() const;
  void drawWall(Direction) const;
  void setWall(Direction, bool);
  bool hasWall(Direction) const;
  bool wasVisited(Direction) const;

  int getX() const;
  int getY() const;
  void setCoordinate(int, int);

  bool hasNeighbour(Direction) const;
  GridElement* getNeighbour(Direction) const;
  void setNeighbour(Direction, GridElement*);

  float neighbourDistance(GridElement const*) const;
  int manhattanDistance(GridElement const*) const;

  void visit();
  void mark();
  bool hasParent() const;
  GridElement* getParent() const;
  void setParent(GridElement*);
  int getPathLength() const;
  void setPathLength(int);
  int getDistance() const;
  void setDistance(int);

 private:
  int x, y;

  GridElement* neighbours[N_DIRECTIONS];
  bool walls[N_DIRECTIONS];

  // variables for maze generation and path finding
  bool visited;
  bool marked;

  GridElement* parent;

  int path_length;
  int distance;
};

#endif /* GridElement_hpp */
