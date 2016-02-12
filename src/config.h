//
// Created by Christian Velez on 2/11/16.
//

#ifndef GLFW_TEST_CONFIG_H
#define GLFW_TEST_CONFIG_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "callbacks.h"
#include "util.h"


namespace Config {
    void setGLFWConfig();
    void setGLContext();
    GLFWwindow* createWindow(std::string winName, unsigned winWidth, unsigned winHeight);
}

#endif //GLFW_TEST_CONFIG_H
