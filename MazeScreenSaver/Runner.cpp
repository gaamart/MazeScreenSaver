#include "Runner.h"
#include <array>

Runner::Runner(Maze& maze):
    sprites{ sprites },
    currentDirection{ DirectionLabel::South },
    state{ RunnerState::NeedToDefineWhereToGo } {
    
    auto availableDirections = maze.getCellAvailableDirections(currentMatrixLine, currentMatrixColumn);
    auto initialDirection = availableDirections.front();

    currentVector = initialDirection.normalizedVector;
    switch (initialDirection.heading)
    {
        case DirectionLabel::South: {
            currentCameraAngle = glm::half_pi<float>();
            targetCameraAngle = currentCameraAngle;
            break;
        }
        case DirectionLabel::East: {
            currentCameraAngle = 0.0f;
            targetCameraAngle = currentCameraAngle;
            break;
        }
        default:
            break;
    }

    auto initialCameraPosition{ glm::vec3((currentPositionX * 0.5f) - 1.0f, 0.0f, ((currentPositionZ * 0.5f) - 1.0f)) };
    camera = Camera{ initialCameraPosition, currentCameraAngle };
}

void Runner::move(Maze& maze, float deltaTime){
    switch (state){
        case RunnerState::NeedToDefineWhereToGo:{
            Compass compass{};
            auto isStuck = true;

            for (auto const &direction : maze.getCellAvailableDirections(currentMatrixLine, currentMatrixColumn)) {
                auto nextLine = currentMatrixLine + direction.lineMovement;
                auto nextColumn = currentMatrixColumn + direction.columnMovement;

                if (not maze.checkCellWasVisited(nextLine, nextColumn)){
                    nextVector = direction.normalizedVector;
                    currentDirection = direction;
                    backTracking.push(compass.getOppositeDirection(direction));
                    maze.setCellAsVisited(nextLine, nextColumn);
                    currentMatrixLine = nextLine;
                    currentMatrixColumn = nextColumn;
                    isStuck = false;
                    break;
                }
            }

            if (isStuck){
                auto lastDirection = backTracking.top();
                backTracking.pop();                
                nextVector = lastDirection.normalizedVector;
                currentDirection = lastDirection;
                currentMatrixLine += lastDirection.lineMovement;
                currentMatrixColumn += lastDirection.columnMovement;
            }
            state = RunnerState::NeedToDefineRotationAngle;
            break;
        }
        case RunnerState::NeedToDefineRotationAngle:{
            auto dotResult = glm::dot(currentVector, nextVector);
            auto angle = glm::acos(dotResult);

            if (angle == glm::zero<float>()){
                state = RunnerState::MoveToNextLocation;
            } else if (angle == glm::pi<float>()){
                targetCameraAngle += angle;
                state = RunnerState::RotateItSelfClockWise;
            }
            else if (angle == glm::half_pi<float>()){
                glm::vec3 crossResult = glm::cross(currentVector, nextVector);
                if (crossResult.y == 1){
                    targetCameraAngle -= angle;
                    state = RunnerState::RotateItSelfCounterClockWise;
                } else {
                    targetCameraAngle += angle;
                    state = RunnerState::RotateItSelfClockWise;
                }
            }
            break;
        }
        case RunnerState::RotateItSelfClockWise:{
            if (currentCameraAngle < targetCameraAngle){
                currentCameraAngle += runnerAngularSpeed * deltaTime;
                camera.updateCameraVectors(currentCameraAngle);
            } else {
                currentCameraAngle = targetCameraAngle;
                currentVector = nextVector;
                state = RunnerState::MoveToNextLocation;
            }
            break;
        }
        case RunnerState::RotateItSelfCounterClockWise:{
            if (currentCameraAngle > targetCameraAngle){
                currentCameraAngle -= runnerAngularSpeed * deltaTime;
                camera.updateCameraVectors(currentCameraAngle);
            } else {
                currentCameraAngle = targetCameraAngle;
                currentVector = nextVector;
                state = RunnerState::MoveToNextLocation;
            }
            break;
        }
        case RunnerState::MoveToNextLocation:{
            switch (currentDirection.heading){
                case DirectionLabel::North:{
                    if (currentPositionZ > currentMatrixColumn){
                        currentPositionZ -= runnerSpeed * deltaTime;
                        camera.setNewPosition(glm::vec3((currentPositionX * 0.5f) - 1.0f, 0.0f, ((currentPositionZ * 0.5f) - 1.0f)));
                    } else {
                        currentPositionZ = static_cast<float>(currentMatrixColumn);
                        if (maze.itsTheEnd(currentMatrixLine, currentMatrixColumn)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }
                case DirectionLabel::South:{
                    if (currentPositionZ < currentMatrixColumn){
                        currentPositionZ += runnerSpeed * deltaTime;
                        camera.setNewPosition(glm::vec3((currentPositionX * 0.5f) - 1.0f, 0.0f, ((currentPositionZ * 0.5f) - 1.0f)));
                    } else {
                        currentPositionZ = static_cast<float>(currentMatrixColumn);
                        if (maze.itsTheEnd(currentMatrixLine, currentMatrixColumn)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }      
                case DirectionLabel::East:{
                    if (currentPositionX < currentMatrixLine){
                        currentPositionX += runnerSpeed * deltaTime;
                        camera.setNewPosition(glm::vec3((currentPositionX * 0.5f) - 1.0f, 0.0f, ((currentPositionZ * 0.5f) - 1.0f)));
                    } else {
                        currentPositionX = static_cast<float>(currentMatrixLine);
                        if (maze.itsTheEnd(currentMatrixLine, currentMatrixColumn)) {
                            state = RunnerState::FoundTheMazeEnd;
                        } else {
                            state = RunnerState::NeedToDefineWhereToGo;
                        }
                    }
                    break;
                }
                case DirectionLabel::West:{
                    if (currentPositionX > currentMatrixLine){
                        currentPositionX -= runnerSpeed * deltaTime;
                        camera.setNewPosition(glm::vec3((currentPositionX * 0.5f) - 1.0f, 0.0f, ((currentPositionZ * 0.5f) - 1.0f)));
                    } else {
                        currentPositionX = static_cast<float>(currentMatrixLine);
                        if (maze.itsTheEnd(currentMatrixLine, currentMatrixColumn)) {
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

glm::mat4 Runner::getView() {
    return camera.getViewMatrix();
}

bool Runner::foundTheMazeEnd() {
    return (state == RunnerState::FoundTheMazeEnd);
}
