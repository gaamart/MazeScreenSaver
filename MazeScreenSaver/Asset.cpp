#include "Asset.h"

Asset::Asset(Sprite sprite):
	sprite{ sprite },
	modelMatrix{ glm::mat4(1.0f) } {
}

void Asset::updateSprite(Sprite newSprite) {
	sprite = newSprite;
}

void Asset::addPosition(glm::vec3 position) {
	modelMatrix = glm::translate(modelMatrix, position);
}

void Asset::addScale(glm::vec3 scale) {
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Asset::addRotation(float angle, glm::vec3 rotation) {
	modelMatrix = glm::rotate(modelMatrix, angle, rotation);
}

void Asset::draw() {
	sprite.drawAt(modelMatrix);
}