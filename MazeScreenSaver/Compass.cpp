#include "Compass.h"

Compass::Compass():
    directionsMap{
       { DirectionLabel::North, Direction{ DirectionLabel::North, 0, -1, glm::vec3{0.0f, 0.0f, -1.0f }} },
       { DirectionLabel::South, Direction{ DirectionLabel::South, 0, 1, glm::vec3{ 0.0f, 0.0f, 1.0f }} },
       { DirectionLabel::East, Direction{ DirectionLabel::East, 1, 0, glm::vec3{ 1.0f, 0.0f, 0.0f }} },
       { DirectionLabel::West, Direction{ DirectionLabel::West, -1, 0, glm::vec3{ -1.0f, 0.0f, 0.0f }} }
    },
    oppositeDirectionsMap{
       { DirectionLabel::North, DirectionLabel::South },
       { DirectionLabel::South, DirectionLabel::North },
       { DirectionLabel::East, DirectionLabel::West },
       { DirectionLabel::West, DirectionLabel::East }
    } {

}

Direction Compass::getOppositeDirection(Direction direction) {
    auto opposite = oppositeDirectionsMap.at(direction.heading);
    return directionsMap.at(opposite);
}

std::vector<Direction> Compass::getAllDirectionsShuffled() {
    auto directionsVector = std::vector<Direction>{};
    for (auto const& item : directionsMap) {
        auto direction = item.second;
        directionsVector.push_back(direction);
    }

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(directionsVector.begin(), directionsVector.end(), std::default_random_engine(seed));
    return directionsVector;
}