#pragma once

#include <vector>
#include "MazeCell.h"
#include "Compass.h"
#include "Sprite.h"

enum class WallsState { Rising, Dropping, Done };

constexpr int mazeSize = 10;
constexpr int initialLine = 0;
constexpr int initialColumn = 0;
constexpr float wallSpeed = 0.5f;

class Maze
{
private:
	WallsState wallsState;
	int biggestPassageLenght;
	int exitLine;
	int exitColumn;
	float wallLevel;
	std::map<SpriteLabel, Sprite> sprites;

	std::unique_ptr<MazeCell> maze[mazeSize][mazeSize];
	void createMazeGrid(int initialLine, int initialColumn, std::map<SpriteLabel, Sprite> sprites);
	void carve_passage(int line, int column, int passageLenght);
	void setCellAsExit(Sprite exitSprite);
	std::map<DirectionLabel, Direction> getDirectionsMapShuffled();

public:
	Maze(std::map<SpriteLabel, Sprite> sprites);
	void setCellAsVisited(int line, int column);
	bool checkCellWasVisited(int line, int column);
	std::vector<Direction> getCellAvailableDirections(int line, int column);
	bool itsTheEnd(int line, int column);
	bool itsWallsAreMoving();
	void draw(float deltaTime);
};

