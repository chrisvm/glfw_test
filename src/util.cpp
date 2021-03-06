//
// Created by Christian Velez on 1/25/16.
//

#include "util.h"

namespace Util {
    char* fileToBuffer(char const * file) {
        FILE *fptr;
        long length;
        char *buf;

        // open file
        fptr = fopen(file, "rb");
        // return null if error opening
        if (!fptr) {
            return NULL;
        }

        // get length of file
        fseek(fptr, 0, SEEK_END);
        length = ftell(fptr);

        // allocate mem and read
        buf = (char*) malloc(length + 1);
        fseek(fptr, 0, SEEK_SET);
        fread(buf, length, 1, fptr);

        // close the file
        fclose(fptr);

        // null terminator
        buf[length] = 0;

        return buf;
    }

    void printHeader() {
        // print opengl version
        printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
        char resolved_path[512];
        realpath(".", resolved_path);
        printf("CWD: %s\n", resolved_path);
    }

    void err_exit(const char* desc, bool glfwDestroy) {
        fputs(desc, stderr);
        fputs("\n", stderr);
        if (glfwDestroy) {
            glfwTerminate();
        }
        exit(EXIT_FAILURE);
    }

    SOILImage* loadImage(const char* img_path) {
        SOILImage *ret = new SOILImage();
        ret->path = img_path;
        ret->image = SOIL_load_image(img_path, &ret->width, &ret->height, 0, SOIL_LOAD_RGB);
        if (ret->image == NULL) {
            delete ret;
            return NULL;
        }
        return ret;
    }
}