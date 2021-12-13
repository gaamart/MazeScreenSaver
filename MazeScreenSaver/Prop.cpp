#include "Prop.h"

Prop::Prop(Shader shader) : shader{ shader } {
}

void Prop::cleanBuffers() {
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
}

void Prop::bind() {
    glBindVertexArray(vertexArrayObject);
}

void Prop::setColor(glm::vec3 color) {
    shader.setVec3("ourColor", color);
}

void Prop::setTransformation(glm::mat4 modelMatrix) {
    shader.setMat4("model", modelMatrix);
}