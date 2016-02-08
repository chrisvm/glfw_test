//
// Created by Christian Velez on 1/30/16.
//

#ifndef GLFW_TEST_CALLBACKS_H
#define GLFW_TEST_CALLBACKS_H
#include <stdio.h>
#include <map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Callbacks {

    // The error callback will just print any errors that GLFW hits.
    void error_callback(int error, const char* description);

    // The key callback generally handles any input, but we'll just use the ESC key in this example.
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    int getKey(int key);

    glm::vec2 getMouse();

    void resetMouse();

    void setWindow(GLFWwindow* win);

    glm::vec2 getWindowSize();
}

#endif //GLFW_TEST_CALLBACKS_H
