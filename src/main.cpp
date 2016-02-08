#define BUFFER_OFFSET(i) ((void*)(i))
#include <stdio.h>
#include <cmath>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl/GLShader.h"
#include "gl/GLProgram.h"
#include "callbacks.h"
#include "game_object/CubeObject.h"
#include "camera.h"



int main() {
    // print header info
    fputs("Starting GLFW3 test\n", stdout);

    // init glfw, check if fail
    if (!glfwInit()) {
        Util::err_exit("Failed to init GLFW, exiting.\n", false);
    } else printf("Inited GLFW\n");

    // set error callback
    glfwSetErrorCallback(Callbacks::error_callback);

    // Set up OpenGL options.
    // Use OpenGL verion 3.3,
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible,
    // i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Indicate we only want the newest core profile, rather than using backwards compatible
    // and deprecated features.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Make the window resize-able.
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create our window
    int wWidth = 800, wHeight = 600;
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "GLFW Test", NULL, NULL);

    // window failed to be created
    if (!window) {
        // exit with error
        Util::err_exit("Failed to create GLFW window.", true);
    }

    // use this window as the default context
    glfwMakeContextCurrent(window);

    // set keyboard callback
    Callbacks::setWindow(window);
    glfwSetKeyCallback(window, Callbacks::key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // init glew with all extensions
    glewExperimental = GL_TRUE;
    glewInit();
    printf("Inited GLEW\n");

    // print header
    Util::printHeader();
    glEnable(GL_DEPTH_TEST);
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
    CubeObject cube1(&program), cube2(&program);
    cube1.move(glm::vec3(0.0f, 2.0f, 0.0f));
    cube2.move(glm::vec3(0.0f, -2.0f, 0.0f));

    // create texture and load to gpu
    cube1.addTexture("assets/images/normals/crystalite_color.jpg");
    cube2.addTexture("assets/images/normals/crystalite_bump.jpg");

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

        // draw debug axis
        // TODO: draw debug axis

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}