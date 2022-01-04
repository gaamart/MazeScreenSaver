#include "Square.h"

Square::Square(){
    float vertices[] = {
        //Positions             //Texture
        0.5f,   0.5f, 0.0f,     1.0f, 1.0f,
        0.5f,  -0.5f, 0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f
    };

    unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };
    
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Square::cleanBuffers() {
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
}

void Square::draw() {
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
