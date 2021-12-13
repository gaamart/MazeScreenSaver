#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "DirectionHelper.h"
#include "Maze.h"
#include "Square.h"

enum class RunnerState { NeedToDefineWhereToGo, NeedToDefineRotationAngle, RotateItSelfClockWise, RotateItSelfCounterClockWise, MoveToNextLocation, FoundTheMazeEnd };
constexpr float speed = 0.5f;
constexpr float angularSpeed = 0.5f;

class Runner
{
private:
	Square square;
	glm::vec3 nextVector;
	glm::vec3 currentVector;

	DirectionLabel currentDirection;

	int matrixPositionX;
	int matrixPositionY;

	float currentPositionX;
	float currentPositionY;
	float currentAngle;
	float targetAngle;

	RunnerState state;
	std::stack<DirectionLabel> backTracking;

public:
	Runner(Square square);
	void draw();
	void movementLogic(Maze& maze, float deltaTime);
	bool FoundTheMazeEnd();
};

