#include "Runner.h"
#include <array>

Runner::Runner(Square square):
    square{ square },
    matrixPositionX{ 0 },
    matrixPositionY{ 0 },
    currentPositionX{ 0.0f }, 
    currentPositionY{ 0.0f }, 
    currentAngle{ 0.0f }, 
    targetAngle{ 0.0f }, 
    state{ RunnerState::NeedToDefineWhereToGo }{
}

void Runner::draw(){
    square.setColor(glm::vec3(0.85f, 0.24f, 0.92f));
    square.bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((currentPositionX * 0.5f) - 1.0f, ((-currentPositionY * 0.5f) + 1.0f), 0.0f)); //move to the correct place in the grid 
    model = glm::rotate(model, currentAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    square.setTransformation(model);
    square.draw();
}

void Runner::movementLogic(Maze& maze, float deltaTime){
    switch (state){
        case RunnerState::NeedToDefineWhereToGo:{
            bool isStuck = true;
            auto directionsMap = DirectionHelper::getDirectionsMap();
            
            for (auto const &direction : DirectionHelper::getAllDirections(true)) {
                int nx = matrixPositionX + direction.lineMovement;
                int ny = matrixPositionY + direction.columnMovement;

                if (maze.checkCellAvailableDirection(matrixPositionX, matrixPositionY, direction.facing) && !maze.checkCellWasVisited(nx, ny)){
                    nextVector = directionsMap.at(direction.facing).vector;
                    if (matrixPositionX == initialLine && matrixPositionY == initialColumn) {
                        currentVector = nextVector;
                    }

                    currentDirection = direction.facing;
                    backTracking.push(direction.opposite);
                    maze.setCellAsVisited(nx, ny);
                    matrixPositionX = nx;
                    matrixPositionY = ny;
                    isStuck = false;
                    break;
                }
            }

            if (isStuck){
                DirectionLabel lastPosition = backTracking.top();
                backTracking.pop();

                for (auto const &direction : DirectionHelper::getAllDirections(true)){
                    if (direction.facing == lastPosition){
                        nextVector = directionsMap.at(direction.facing).vector;
                        currentDirection = direction.facing;
                        matrixPositionX += direction.lineMovement;
                        matrixPositionY += direction.columnMovement;
                    }
                }
            }
            state = RunnerState::NeedToDefineRotationAngle;
            break;
        }
        case RunnerState::NeedToDefineRotationAngle:{
            float dotResult = glm::dot(currentVector, nextVector);
            float angle = glm::acos(dotResult);

            if (angle == glm::zero<float>()){
                state = RunnerState::MoveToNextLocation;
            } else if (angle == glm::pi<float>()){
                targetAngle += angle;
                state = RunnerState::RotateItSelfClockWise;
            }
            else if (angle == glm::half_pi<float>()){
                glm::vec3 crossResult = glm::cross(currentVector, nextVector);
                if (crossResult.z == 1){
                    targetAngle += angle;
                    state = RunnerState::RotateItSelfClockWise;
                } else {
                    targetAngle -= angle;
                    state = RunnerState::RotateItSelfCounterClockWise;
                }
            }
            break;
        }
        case RunnerState::RotateItSelfClockWise:{
            if (currentAngle < targetAngle){
                currentAngle += angularSpeed * deltaTime;
            } else {
                currentAngle = targetAngle;
                currentVector = nextVector;
                state = RunnerState::MoveToNextLocation;
            }
            break;
        }
        case RunnerState::RotateItSelfCounterClockWise:{
            if (currentAngle > targetAngle){
                currentAngle -= angularSpeed * deltaTime;
            } else {
                currentAngle = targetAngle;
                currentVector = nextVector;
                state = RunnerState::MoveToNextLocation;
            }
            break;
        }
        case RunnerState::MoveToNextLocation:{
            switch (currentDirection){
                case DirectionLabel::North:{
                    if (currentPositionY > matrixPositionY){
                        currentPositionY -= speed * deltaTime;
                    } else {
                        currentPositionY = matrixPositionY;
                        if (maze.itsTheMazeEnd(currentPositionX, currentPositionY)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }
                case DirectionLabel::South:{
                    if (currentPositionY < matrixPositionY){
                        currentPositionY += speed * deltaTime;
                    } else {
                        currentPositionY = matrixPositionY;
                        if (maze.itsTheMazeEnd(currentPositionX, currentPositionY)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }      
                case DirectionLabel::East:{
                    if (currentPositionX < matrixPositionX){
                        currentPositionX += speed * deltaTime;
                    } else {
                        currentPositionX = matrixPositionX;
                        if (maze.itsTheMazeEnd(currentPositionX, currentPositionY)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }
                case DirectionLabel::West:{
                    if (currentPositionX > matrixPositionX){
                        currentPositionX -= speed * deltaTime;
                    } else {
                        currentPositionX = matrixPositionX;
                        if (maze.itsTheMazeEnd(currentPositionX, currentPositionY)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

bool Runner::FoundTheMazeEnd() {
    return (state == RunnerState::FoundTheMazeEnd);
}
