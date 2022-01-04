#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Sprite.h"

class Asset
{
private:
	Sprite sprite;
	glm::mat4 modelMatrix;

public:
	Asset(Sprite sprite);
	void updateSprite(Sprite newSprite);
	void addPosition(glm::vec3 position);
	void addScale(glm::vec3 scale);
	void addRotation(float angle, glm::vec3 rotation);
	void draw();
};

