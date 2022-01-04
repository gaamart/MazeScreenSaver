#include "MazeCell.h"

MazeCell::MazeCell(int line, int column, std::map<SpriteLabel, Sprite> sprites) : 
    visited{ false }, 
    floorAsset{ sprites.at(SpriteLabel::Floor) }, 
    ceilingAsset{ sprites.at(SpriteLabel::Ceiling) }
{
    auto gridplace{ glm::vec3((line * 0.5f) - 1.0f, 0.0f, ((column * 0.5f) - 1.0f)) };
    auto cellScale{ glm::vec3(0.5f, 0.5f, 0.5f) };

    floorAsset.addPosition(gridplace);
    floorAsset.addPosition(glm::vec3(0.0f, -cellRadius, 0.0f)); //move floor down
    floorAsset.addRotation(glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    floorAsset.addScale(cellScale);

    ceilingAsset.addPosition(gridplace);
    ceilingAsset.addPosition(glm::vec3(0.0f, cellRadius, 0.0f)); //move ceiling up
    ceilingAsset.addRotation(glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    ceilingAsset.addScale(cellScale);

    Asset northWall{ sprites.at(SpriteLabel::Wall) };
    northWall.addPosition(gridplace);
    northWall.addPosition(glm::vec3(0.0f, -cellDiameter, -cellRadius)); //move wall to location
    northWall.addScale(cellScale);
    wallAssets.insert({ DirectionLabel::North, northWall });

    Asset southWall{ sprites.at(SpriteLabel::Wall) };
    southWall.addPosition(gridplace);
    southWall.addPosition(glm::vec3(0.0f, -cellDiameter, cellRadius)); //move wall to location
    southWall.addScale(cellScale);
    wallAssets.insert({ DirectionLabel::South, southWall });

    Asset eastWall{ sprites.at(SpriteLabel::Wall) };
    eastWall.addPosition(gridplace);
    eastWall.addPosition(glm::vec3(cellRadius, -cellDiameter, 0.0f)); //move wall to location
    eastWall.addRotation(glm::half_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate wall
    eastWall.addScale(cellScale);
    wallAssets.insert({ DirectionLabel::East, eastWall });

    Asset westWall{ sprites.at(SpriteLabel::Wall) };
    westWall.addPosition(gridplace);
    westWall.addPosition(glm::vec3(-cellRadius, -cellDiameter, 0.0f)); //move wall to location
    westWall.addRotation(glm::half_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate wall
    westWall.addScale(cellScale);
    wallAssets.insert({ DirectionLabel::West, westWall });
}

void MazeCell::setExit(Sprite exitSprite)
{
    Compass compass{};
    auto availableDirection = getAvailableDirections().front();
    auto exitWallDirection = compass.getOppositeDirection(availableDirection);
    auto exitAsset = wallAssets.at(exitWallDirection.heading);

    exitAsset.updateSprite(exitSprite);  
    wallAssets.erase(exitWallDirection.heading);
    wallAssets.insert({ exitWallDirection.heading, exitAsset });
}

std::vector<Direction> MazeCell::getAvailableDirections() 
{
    return directions;
}

bool MazeCell::checkIfVisited()
{
	return visited;
}

bool MazeCell::checkIfEmpty()
{
	return directions.empty();
}

void MazeCell::wasVisited()
{
	visited = true;
}

void MazeCell::addDirection(Direction direction)
{
	directions.push_back(direction);
    wallAssets.erase(direction.heading);
}

void MazeCell::moveWallsTo(glm::vec3 position) {
    for (auto &item : wallAssets) {
        item.second.addPosition(position);
    }
}

void MazeCell::draw() {
    floorAsset.draw();
    ceilingAsset.draw();
    for (auto const& item : wallAssets) {
        auto asset = static_cast<Asset>(item.second);
        asset.draw();
    }
}