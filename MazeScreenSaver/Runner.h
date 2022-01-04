#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "Compass.h"
#include "Maze.h"
#include "Square.h"
#include "Camera.h"

enum class RunnerState { NeedToDefineWhereToGo, NeedToDefineRotationAngle, RotateItSelfClockWise, RotateItSelfCounterClockWise, MoveToNextLocation, FoundTheMazeEnd, Waiting };
constexpr float runnerSpeed = 1.5f;
constexpr float runnerAngularSpeed = 1.5f;

class Runner
{
private:
	Square square;
	glm::vec3 nextVector;
	glm::vec3 currentVector;

	Direction currentDirection;
	Camera camera;

	int currentMatrixLine;
	int currentMatrixColumn;

	float currentPositionX;
	float currentPositionZ;
	float currentCameraAngle;
	float targetCameraAngle;

	RunnerState state;
	std::stack<Direction> backTracking;
	std::map<SpriteLabel, Sprite> sprites;

public:
	Runner(Maze& maze);
	void move(Maze& maze, float deltaTime);
	glm::mat4 getView();
	bool foundTheMazeEnd();
};

