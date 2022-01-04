#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* fileName, FileExtension fileExtension):
    ID{ 0 },
    width{ 0 },
    height{ 0 },
    nrChannels{ 0 },
    unit{ 0 } {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    switch (fileExtension)
    {
        case FileExtension::JPEG: {
            unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, STBI_default);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
            break;
        }
        case FileExtension::PNG: {
            unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, STBI_rgb_alpha);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
            break;
        }
        default:
            break;
    } 
    glGenerateMipmap(GL_TEXTURE_2D);
    unit = globalUnitOrder++;
}

unsigned int Texture::getUnit() {
    return unit;
}

void Texture::bind() {    
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}