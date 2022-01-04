#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Square
{
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	unsigned int elementBufferObject;

public:
	Square();
	void cleanBuffers();
	void draw();
};

