#pragma once

#
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <thread>

enum class DirectionLabel { North, South, East, West };

struct Direction
{
	DirectionLabel facing;
	DirectionLabel opposite;
	int lineMovement;
	int columnMovement;
	glm::vec3 vector;
};

namespace DirectionHelper
{
	std::vector<Direction> getAllDirections(bool shuffle = false);
	std::map<DirectionLabel, Direction> getDirectionsMap();
};