#define BUFFER_OFFSET(i) ((void*)(i))
#include <stdio.h>
#include <cmath>
#include <string>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl/GLShader.h"
#include "gl/GLProgram.h"
#include "game_object/CubeObject.h"
#include "engine/Lightning.h"
#include "callbacks.h"
#include "camera.h"
#include "config.h"
#include "game_object/MeshObject.h"
#include "engine/Game.h"


int main() {
    // print header info
    printf("Starting GLFW3\n");

    // init glfw, check if fail
    if (!glfwInit()) {
        Util::err_exit("Failed to init GLFW, exiting.\n", false);
    } else printf("Inited GLFW\n");

    // set error callback
    glfwSetErrorCallback(Callbacks::error_callback);

    // set context and config
    Config::setGLFWConfig();

    // create our window
    int wWidth = 800, wHeight = 600;
    GLFWwindow* window = Config::createWindow("GLFW Test", wWidth, wHeight);

    // set up context
    Config::setGLContext();

    // set clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // create engine instance
    Engine::Game* game = new Engine::Game();
    game->init();
    game->setAssetLocation("assets");

    // get standard program
    GL::Program* program = game->loader()->getProgram("standard");
    program->use();


    // create camera
    Camera::Camera * camera = new Camera::Camera(
            program->uniformLocation("view"),
            program->uniformLocation("proj"),
            program->uniformLocation("EyeWorldPos")
    );

    // create mesh cube
    MeshObject cube(game->loader()->getObjectFile("cube"), program, game);
    cube.addTexture("cube/cube_texture.png");
    cube.scale(0.5f);

    // create light
    Engine::Lightning *light = new Engine::Lightning(program);

    // render loop
    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {

        // get time
        auto t_now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        t_start = t_now;

        // camera view
        camera->FPSCam(deltaTime);

        // Clear the entire buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set lights
        light->update();

        // render cube
        cube.rotate(deltaTime, glm::vec3(1.0f, 1.0f, 0));
        cube.render();

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}