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
#include "engine/Game.h"
#include "callbacks.h"
#include "camera.h"
#include "config.h"


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

    // create program
    GL::Program program;

    // attach and create shaders
    GL::Shader *vs = new GL::Shader(GL_FRAGMENT_SHADER, "assets/shaders/fragment/standard.frag");
    GL::Shader *fs = new GL::Shader(GL_VERTEX_SHADER, "assets/shaders/vertex/standard.vert");
    program.attachShader(vs);
    program.attachShader(fs);
    printf("Shader compilation was successful\n");

    // link and use the program
    program.link();
    program.use();

    // create cubes
    CubeObject cube1(&program), cube2(&program), cube3(&program);
    cube1.move(glm::vec3(0.0f, 2.0f, 0.0f));
    cube2.move(glm::vec3(0.0f, -2.0f, 0.0f));
    cube3.move(glm::vec3(0.0f, 0.0f, 0.0f));

    // create texture and load to gpu
    cube1.addTexture("assets/images/normals/crystalite_color.jpg");
    cube2.addTexture("assets/images/normals/crystalite_bump.jpg");
    cube3.addTexture("assets/images/normals/crystalite_normal.jpg");

    // create camera
    Camera::Camera * camera = new Camera::Camera(
            program.uniformLocation("view"),
            program.uniformLocation("proj")
    );

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

        // render cube
        cube1.render();
        cube2.render();
        cube3.render();

        // draw debug axis
        // TODO: draw debug axis

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}