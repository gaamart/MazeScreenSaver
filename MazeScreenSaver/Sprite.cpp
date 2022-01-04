#include "Sprite.h"

Sprite::Sprite(Shader shader, Square square, Texture texture) : 
	shader{ shader }, 
	square{ square },
	texture{ texture } {
}

void Sprite::drawAt(glm::mat4 modelMatrix) {
	shader.setInt("textureUnit", texture.getUnit());
	shader.setMat4("model", modelMatrix);
	square.draw();
}