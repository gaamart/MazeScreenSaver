#include "Maze.h"

Maze::Maze(std::map<SpriteLabel, Sprite> sprites) :
    biggestPassageLenght{ 0 },
    exitLine{ 0 },
    exitColumn{ 0 },
    sprites{ sprites },
    wallLevel{ -cellDiameter },
    wallsState{ WallsState::Rising } {
    createMazeGrid(initialLine, initialColumn, sprites);
    setCellAsVisited(initialLine, initialColumn);
    setCellAsExit(sprites.at(SpriteLabel::Exit));
}

void Maze::carve_passage(int line, int column, int passageLenght){
    Compass compass{};
    for (auto const &direction : compass.getAllDirectionsShuffled()){
        int nextLine = line + direction.lineMovement;
        int nextColumn = column + direction.columnMovement;

        if ((nextColumn >= 0 and nextColumn < mazeSize) and (nextLine >= 0 and nextLine < mazeSize) and (maze[nextLine][nextColumn]->checkIfEmpty())){
            passageLenght++;
            if (passageLenght > biggestPassageLenght) {
                biggestPassageLenght = passageLenght;
                exitLine = nextLine;
                exitColumn = nextColumn;
            }

            maze[line][column]->addDirection(direction);
            maze[nextLine][nextColumn]->addDirection(compass.getOppositeDirection(direction));
            carve_passage(nextLine, nextColumn, passageLenght);
        }
    }
    passageLenght--;
}

void Maze::setCellAsVisited(int line, int column){
    maze[line][column]->wasVisited();
}

void Maze::setCellAsExit(Sprite exitSprite) {
    maze[exitLine][exitColumn]->setExit(exitSprite);
}

bool Maze::checkCellWasVisited(int line, int column){
    return maze[line][column]->checkIfVisited();
}

std::vector<Direction> Maze::getCellAvailableDirections(int line, int column) {
    return maze[line][column]->getAvailableDirections();
}

bool Maze::itsWallsAreMoving() {
    return (wallsState != WallsState::Done);
}

bool Maze::itsTheEnd(int line, int column) {
    if (line == exitLine and column == exitColumn) {
        wallsState = WallsState::Dropping;
        return true;
    } else {
        return false;
    }
}

void Maze::draw(float deltaTime){
    
    switch (wallsState)
    {
        case WallsState::Rising: {
            wallLevel += wallSpeed * deltaTime;
            if (wallLevel < cellDiameter) {
                for (int line = 0; line < mazeSize; line++) {
                    for (int column = 0; column < mazeSize; column++) {
                        maze[line][column]->moveWallsTo(glm::vec3(0.0f, wallSpeed * deltaTime, 0.0f));
                        maze[line][column]->draw();
                    }
                }
            } else {
                wallLevel = cellDiameter;
                wallsState = WallsState::Done;
            }
            break;
        }
        case WallsState::Done: {
            for (int line = 0; line < mazeSize; line++) {
                for (int column = 0; column < mazeSize; column++) {
                    maze[line][column]->draw();
                }
            }
            break;
        }   
        case WallsState::Dropping: {
            wallLevel -= wallSpeed * deltaTime;
            if (wallLevel > -cellDiameter) {
                for (int line = 0; line < mazeSize; line++) {
                    for (int column = 0; column < mazeSize; column++) {
                        maze[line][column]->moveWallsTo(glm::vec3(0.0f, -wallSpeed * deltaTime, 0.0f));
                        maze[line][column]->draw();
                    }
                }
            } else {
                wallLevel = -cellDiameter;
                wallsState = WallsState::Done;
            }
            break;
        }
        default:
            break;
    }
}

void Maze::createMazeGrid(int initialLine, int initialColumn, std::map<SpriteLabel, Sprite> sprites) {
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++)
            maze[i][j] = std::make_unique<MazeCell>(i, j, sprites);
    }

    carve_passage(initialLine, initialColumn, 0);
}