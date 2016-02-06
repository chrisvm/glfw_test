//
// Created by Christian Velez on 1/30/16.
//
#include "callbacks.h"


namespace Callbacks {
    // info on keys
    std::map<int, int> keys;
    glm::vec2 mouse;

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

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        mouse.x = xpos;
        mouse.y = ypos;
    }

    int getKey(int key) {
        return keys[key];
    }

    glm::vec2 getMouse() {
        return mouse;
    }
}