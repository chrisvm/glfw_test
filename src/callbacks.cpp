//
// Created by Christian Velez on 1/30/16.
//
#include "callbacks.h"


namespace Callbacks {
    // info on keys
    std::map<int, int> keys;
    GLFWwindow* _window;

    // The error callback will just print any errors that GLFW hits.
    void error_callback(int error, const char* description) {
        fprintf(stderr, "Error: %u\n%s\n", error, description);
    }

    // The key callback generally handles any input, but we'll just use the ESC key in this example.
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }

        if (action == GLFW_RELEASE) {
            keys[key] = 0;
        } else if (action == GLFW_PRESS) {
            keys[key] = 1;
        }
    }

    int getKey(int key) {
        return keys[key];
    }

    glm::vec2 getMouse() {
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        return glm::vec2(xpos, ypos);
    }

    void resetMouse() {
        int width, height;
        glfwGetWindowSize(_window, &width, &height);
        glfwSetCursorPos(_window, width / 2.0, height / 2.0);
    }

    void setWindow(GLFWwindow* win) {
        _window = win;
    }

    glm::vec2 getWindowSize() {
        int width, height;
        glfwGetWindowSize(_window, &width, &height);
        return glm::vec2(width, height);
    }
}