#include "MazeCell.h"

MazeCell::MazeCell(Rectangle rectangle):
    visited{ false },
    borderLocations{ DirectionLabel::North, DirectionLabel::South, DirectionLabel::East, DirectionLabel::West },
    rectangle{rectangle}
{

}

bool MazeCell::checkDirection(DirectionLabel direction)
{
	return directions.find(direction) != directions.end();
}

std::set<DirectionLabel> MazeCell::getAvailableDirections() 
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

void MazeCell::addDirection(DirectionLabel direction)
{
	directions.insert(direction);
    borderLocations.erase(direction);
}

void MazeCell::draw(int line, int column) {
    rectangle.setColor(glm::vec3(0.0f, 0.0f, 0.0f));
    rectangle.bind();

    for (auto direction : borderLocations) {
        glm::mat4 modelMatrix = glm::mat4(1.0f); //identity matrix
        modelMatrix = glm::translate(modelMatrix, glm::vec3((line * 0.5f) - 1.0f, ((-column * 0.5f) + 1.0f), 0.0f)); //move cell to grid

        switch (direction) {
        case DirectionLabel::North: {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.24f, 0.0f)); //move border to the top
            modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        }
        case DirectionLabel::South: {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.24f, 0.0f)); //move border to the bottom
            modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        }
        case DirectionLabel::East: {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.24f, 0.0f, 0.0f)); //move border to the right
            break;
        }
        case DirectionLabel::West: {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.24f, 0.0f, 0.0f)); //move border to the left
            break;
        }
        default:
            break;
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        rectangle.setTransformation(modelMatrix);
        rectangle.draw();
    }
}