//
// Created by Christian Velez on 1/25/16.
//

#ifndef GLFW_TEST_UTIL_H
#define GLFW_TEST_UTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

namespace Util {
    struct SOILImage {
        int width, height;
        unsigned char * image;
        const char * path;

        void free() {
            SOIL_free_image_data(this->image);
            this->image = NULL;
            delete this;
        }

        char * info() {
            char * format = (char *)"{width=%i, height=%i, path=%s}";
            char * ret = new char[128];
            sprintf(ret, format, this->width, this->height, this->path);
            return ret;
        }
    };

    char* fileToBuffer(char const *file);
    void printHeader();
    void err_exit(const char* desc, bool glfwDestroy);
    SOILImage* loadImage(const char* img_path);
};


#endif //GLFW_TEST_UTIL_H
