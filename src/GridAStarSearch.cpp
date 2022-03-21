//
//  GridAStartSearch.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//	Edited by Anna van der Linden and Kai Ferdelman on 16/01/2019
//

#include "Grid.hpp"

#include <iostream>

#include "PriorityQueue.hpp"

// score comparison class for priority queue
class FScoreCompare {
  public:
    bool operator()(GridElement const* a, GridElement const* b) const {
        return (a->getPathLength() + a->getDistance()) >
               (b->getPathLength() + b->getDistance());
    }
};

GridElement* Grid::aStarSearch(int _posX, int _posY, int _targetX, int _targetY) {
    // priority queue which sorts elements based on the sum of its path length
    // since the start and manhattan distance to the end (path_length and distance
    // are members of GridElement) for A* search
    PriorityQueue<GridElement*, FScoreCompare> queue;
    
	//Start and end element can be anywhere on the grid
	GridElement* start_element = &grid[_posX][_posY];
	GridElement* end_element = &grid[_targetX][_targetY];

	start_element->visit();

	queue.push(start_element);

	bool found_end = false;
	int states = 0, path_length = 0;

	while (!queue.empty()) {
		GridElement* current_element = queue.front();
		queue.pop();

		states++;

		if (current_element == end_element) {
			end_element->mark();
			// found end, so stop
			found_end = true;

			GridElement* prevElement = current_element;
			while (current_element->hasParent()) {
				prevElement = current_element;
				current_element = current_element->getParent();
				current_element->mark();
				path_length++;
				pathLength = path_length;
			}
			// returns next grid rile to move to
			return prevElement;

			//mark all left in queue as visited
			while (!queue.empty()) {
				GridElement* q_element = queue.front();
				q_element->visit();
				queue.pop();
			}

			break;
		}

		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (!current_element->hasWall((Direction)direction) &&
				(!current_element->wasVisited((Direction)direction) || 
					current_element->getPathLength()+1 < current_element->getNeighbour((Direction)direction)->getPathLength())) {
				GridElement* next_element =
					current_element->getNeighbour((Direction)direction);
				next_element->visit();
				next_element->setParent(current_element);
				next_element->setDistance(next_element->manhattanDistance(end_element));
				next_element->setPathLength(current_element->getPathLength()+1);
				queue.push(next_element);
			}
		}


	}

	// print result
	if (!found_end) {
		return &grid[_posX][_posY];
	}
	else {
		std::cout << "A*S(states: " << states << ", path length: " << path_length
			<< ")" << '\n';
	}
}
