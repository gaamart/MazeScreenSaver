#include "DirectionHelper.h"

std::vector<Direction> DirectionHelper::getAllDirections(bool shuffle){
    std::vector<Direction> directions{
        Direction{ DirectionLabel::North, DirectionLabel::South, 0, -1, glm::vec3{0.0f, 1.0f, 0.0f }},
        Direction{ DirectionLabel::South, DirectionLabel::North, 0, 1, glm::vec3{ 0.0f, -1.0f, 0.0f }},
        Direction{ DirectionLabel::East, DirectionLabel::West, 1, 0, glm::vec3{ 1.0f, 0.0f, 0.0f }},
        Direction{ DirectionLabel::West, DirectionLabel::East, -1, 0, glm::vec3{ -1.0f, 0.0f, 0.0f }}
    };

    if (shuffle){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));
    }

    return directions;
}

std::map<DirectionLabel, Direction>  DirectionHelper::getDirectionsMap() {
    return {
        { DirectionLabel::North, Direction{ DirectionLabel::North, DirectionLabel::South, 0, -1, glm::vec3{0.0f, 1.0f, 0.0f }} },
        { DirectionLabel::South, Direction{ DirectionLabel::South, DirectionLabel::North, 0, 1, glm::vec3{ 0.0f, -1.0f, 0.0f }} },
        { DirectionLabel::East, Direction{ DirectionLabel::East, DirectionLabel::West, 1, 0, glm::vec3{ 1.0f, 0.0f, 0.0f }} },
        { DirectionLabel::West, Direction{ DirectionLabel::West, DirectionLabel::East, -1, 0, glm::vec3{ -1.0f, 0.0f, 0.0f } }}
    };
}