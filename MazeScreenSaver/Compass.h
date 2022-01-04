#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include "Direction.h"

class Compass
{
private:
	std::map<DirectionLabel, DirectionLabel> oppositeDirectionsMap;
	std::map<DirectionLabel, Direction> directionsMap;

public:
	Compass();
	Direction getOppositeDirection(Direction direction);
	std::vector<Direction> getAllDirectionsShuffled();
};