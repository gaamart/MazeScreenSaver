#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Shader.h"

class Prop
{
protected:
	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	unsigned int elementBufferObject;
	Shader shader;

public:
	Prop(Shader shader);
	void cleanBuffers();
	void bind();
	void setColor(glm::vec3 color);
	void setTransformation(glm::mat4 transfomationMatrix);
	virtual void draw() = 0;
};


