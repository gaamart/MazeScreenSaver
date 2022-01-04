#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

public:
    Camera() = default;
    Camera(glm::vec3 initialPosition, float initialYaw);
    glm::mat4 getViewMatrix();
    void setNewPosition(glm::vec3 newPosition);
    void updateCameraVectors(float yaw);
};

