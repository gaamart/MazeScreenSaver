#include "Maze.h"
#include <random>
#include <chrono>
#include <thread>
#include <map>
#include <functional>

Maze::Maze(Square square, Rectangle rectangle) : square{ square }, biggestPathLenght{ 0 }, finalPositionX{ 0 }, finalPositionY{ 0 } {
    createMazeGrid(initialLine, initialColumn, rectangle);
    setCellAsVisited(initialLine, initialColumn);
}

void Maze::carve_passage(int cx, int cy, int currentPathLenght){
    for (auto const &direction : DirectionHelper::getAllDirections(true)){
        int nx = cx + direction.lineMovement;
        int ny = cy + direction.columnMovement;

        if ((ny >= 0 && ny < mazeSize) && (nx >= 0 && nx < mazeSize) && (maze[nx][ny]->checkIfEmpty())){
            currentPathLenght++;
            if (currentPathLenght > biggestPathLenght) {
                biggestPathLenght = currentPathLenght;
                finalPositionX = nx;
                finalPositionY = ny;

            }

            maze[cx][cy]->addDirection(direction.facing);
            maze[nx][ny]->addDirection(direction.opposite);
            carve_passage(nx, ny, currentPathLenght);
        }
    }
    currentPathLenght--;
}

void Maze::setCellAsVisited(int cellLine, int cellColumn){
    maze[cellLine][cellColumn]->wasVisited();
}

bool Maze::checkCellWasVisited(int cellLine, int cellColumn){
    return maze[cellLine][cellColumn]->checkIfVisited();
}

bool Maze::checkCellAvailableDirection(int cellLine, int cellColumn, DirectionLabel direction){
    return maze[cellLine][cellColumn]->checkDirection(direction);
}

bool Maze::itsTheMazeEnd(int line, int column) {
    return (line == finalPositionX && column == finalPositionY);
}

void Maze::draw(){
    //MAZE
    square.bind();
    for (int i = 0; i < mazeSize; i++){
        for (int j = 0; j < mazeSize; j++){
            if (i == finalPositionX && j == finalPositionY) {
                square.setColor(glm::vec3(0.0f, 0.0f, 1.0f));
            }
            else {
                square.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
            }
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3((i * 0.5f) - 1.0f, ((-j * 0.5f) + 1.0f), 0.0f)); //move to the correct place in the grid 
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            square.setTransformation(model);
            square.draw();
        }
    }

    //BORDERS
    for (int line = 0; line < mazeSize; line++){
        for (int column = 0; column < mazeSize; column++){
            maze[line][column]->draw(line, column);
        }
    }
}

void Maze::createMazeGrid(int initialLine, int initialColumn, Rectangle rectangle) {
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++)
            maze[i][j] = std::make_unique<MazeCell>(rectangle);
    }

    carve_passage(initialLine, initialColumn, 0);

}


