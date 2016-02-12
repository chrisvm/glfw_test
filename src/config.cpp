//
// Created by Christian Velez on 2/11/16.
//
#include "config.h"

namespace Config {
    void setGLFWConfig() {
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
    }

    GLFWwindow* createWindow(std::string winName, unsigned winWidth, unsigned winHeight) {
        GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, winName.c_str(), NULL, NULL);

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

        return window;
    }

    void setGLContext() {
        // init glew with all extensions
        glewExperimental = GL_TRUE;
        glewInit();
        printf("Inited GLEW\n");

        // print header
        Util::printHeader();
        glEnable(GL_DEPTH_TEST);
    }
}