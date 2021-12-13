#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <set>
#include "DirectionHelper.h"
#include "Rectangle.h"

class MazeCell
{
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	unsigned int elementBufferObject;
	Rectangle rectangle;

	bool visited;
	std::set<DirectionLabel> directions;
	std::set<DirectionLabel> borderLocations;

public:
	MazeCell(Rectangle rectangle);
	void wasVisited();
	bool checkIfVisited();
	bool checkIfEmpty();
	void addDirection(DirectionLabel direction);
	bool checkDirection(DirectionLabel direction);
	std::set<DirectionLabel> getAvailableDirections();
	void draw(int line, int column);
};

