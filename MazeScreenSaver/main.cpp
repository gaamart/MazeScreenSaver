#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <random>
#include <chrono>
#include <thread>
#include "Shader.h"
#include "Maze.h"
#include "MazeCell.h"
#include "Runner.h"
#include "Square.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"

constexpr int screen_width = 800;
constexpr int screen_height = 600;
constexpr float zoom = 45.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "MazeScreenSaver", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader{ "shader.vs", "shader.fs" };
    shader.use();
   
    Square square{};

    Texture container{ "textures/container.jpg", FileExtension::JPEG };
    Texture ceiling{ "textures/ceiling.png", FileExtension::PNG };
    Texture floor{ "textures/floor.png", FileExtension::PNG };
    Texture awesomeface{ "textures/awesomeface.png", FileExtension::PNG };    

    container.bind();
    ceiling.bind();
    floor.bind();
    awesomeface.bind();

    std::map<SpriteLabel, Sprite> baseAssets{
        { SpriteLabel::Wall, Sprite{ shader, square, container } },
        { SpriteLabel::Ceiling, Sprite{ shader, square, ceiling } },
        { SpriteLabel::Floor, Sprite{ shader, square, floor } },
        { SpriteLabel::Exit, Sprite{ shader, square, awesomeface } }
    };

    auto *maze = new Maze{ baseAssets };
    auto *runner = new Runner{ *maze };

    glEnable(GL_DEPTH_TEST);

    auto deltaTime{ 0.0f };
    auto lastFrame{ 0.0f };

    while (not glfwWindowShouldClose(window)){
        auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto view = glm::mat4(1.0f);
        view = runner->getView();
        shader.setMat4("view", view);

        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(zoom), static_cast<float>(screen_width) / static_cast<float>(screen_height), 0.01f, 100.0f);
        shader.setMat4("projection", projection);
        
        if (not runner->foundTheMazeEnd())
        {
            maze->draw(deltaTime);
            if (not maze->itsWallsAreMoving()) {
                runner->move(*maze, deltaTime);
            }
            
        } else {
            if (maze->itsWallsAreMoving()) {
                maze->draw(deltaTime); 
            } else {
                delete maze;
                delete runner;
                maze = new Maze{ baseAssets };
                runner = new Runner{ *maze };
            }

        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    if (maze)
        delete maze;
    if (runner)
        delete runner;

    square.cleanBuffers();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}