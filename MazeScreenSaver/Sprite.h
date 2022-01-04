#pragma once

#include <glad/glad.h>
#include "Shader.h"
#include "Square.h"
#include "Texture.h"

enum class SpriteLabel { Wall, Ceiling, Floor, Exit };

class Sprite
{

private:
	Shader shader;
	Square square;
	Texture texture;

public:
	Sprite(Shader shader, Square square, Texture texture);
	void drawAt(glm::mat4 modelMatrix);
};