#pragma once

#include <glad/glad.h>

enum class FileExtension { JPEG, PNG };

static int globalUnitOrder;

class Texture
{
private:
	unsigned int ID;
	int width;
	int height;
	int nrChannels;
	int unit;

public:
	Texture(const char* fileName, FileExtension fileExtension);
	unsigned int getUnit();
	void bind();
};

