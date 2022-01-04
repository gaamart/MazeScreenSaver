#pragma once

#include "Camera.h"

Camera::Camera(glm::vec3 initialPosition, float initialYaw) :
    position{ initialPosition },
    front{ glm::vec3(0.0f, 0.0f, -1.0f) },
    up{ glm::vec3(0.0f, 1.0f, 0.0f) },
    right { glm::vec3(1.0f, 0.0f, 0.0f) },
    worldUp { up } {
    updateCameraVectors(initialYaw);
}

void Camera::setNewPosition(glm::vec3 newPosition) {
    position = newPosition;
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors(float yaw) {
    auto newFront = glm::vec3{ cos(yaw), 0.0f, sin(yaw) };
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

