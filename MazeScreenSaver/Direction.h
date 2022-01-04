#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class DirectionLabel { North, South, East, West };

struct Direction
{
	DirectionLabel heading;
	int lineMovement;
	int columnMovement;
	glm::vec3 normalizedVector;
};