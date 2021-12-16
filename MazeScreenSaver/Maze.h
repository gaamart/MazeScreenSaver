#pragma once

#include <glad/glad.h>
#include <algorithm>
#include "MazeCell.h"
#include "DirectionHelper.h"
#include "Square.h"
#include "Rectangle.h"
#include <map>

constexpr int mazeSize = 10;
constexpr int initialLine = 0;
constexpr int initialColumn = 0;

class Maze
{
private:
	Square square;
	std::unique_ptr<MazeCell> maze[mazeSize][mazeSize];
	void createMazeGrid(int initialLine, int initialColumn, Rectangle rectangle);
	int biggestPathLenght;
	int finalPositionX;
	int finalPositionY;

public:
	Maze(Square square, Rectangle rectangle);
	void carve_passage(int cx, int cy, int currentPathLenght);
	void setCellAsVisited(int cellLine, int cellColumn);
	bool checkCellWasVisited(int cellLine, int cellColumn);
	bool checkCellAvailableDirection(int cellLine, int cellColumn, DirectionLabel direction);
	bool itsTheMazeEnd(int line, int column);
	void draw();
};

