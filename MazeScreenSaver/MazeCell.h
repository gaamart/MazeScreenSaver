#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "Compass.h"
#include "Sprite.h"
#include "Asset.h"

constexpr float cellRadius = 0.249f;
const float cellDiameter = cellRadius * 2;

class MazeCell
{
private:
	bool visited;
	Asset floorAsset;
	Asset ceilingAsset;
	std::map<DirectionLabel, Asset> wallAssets;
	std::vector<Direction> directions;

public:
	MazeCell(int line, int column, std::map<SpriteLabel, Sprite> sprites);
	void wasVisited();
	bool checkIfVisited();
	bool checkIfEmpty();
	void addDirection(Direction direction);
	std::vector<Direction> getAvailableDirections();
	void setExit(Sprite ExitSprite);
	void moveWallsTo(glm::vec3 position);
	void draw();
	
};

