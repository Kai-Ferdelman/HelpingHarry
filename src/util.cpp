//
//  util.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 22/11/2017.
//

#include "util.hpp"

#include <cmath>
#include <cstdlib>

double distance(double x, double y) {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

double frand(double min, double max) {
  return min + std::rand() / ((double)RAND_MAX / (max - min));
}
