//
// Created by Christian Velez on 1/25/16.
//

#ifndef GLFW_TEST_SHADER_H
#define GLFW_TEST_SHADER_H
#include <GL/glew.h>
#include <string>
#include "../util.h"

namespace GL {
    class Shader {
    public:
        Shader(GLenum shaderType, char const * shaderLocation);
        GLuint getHandle(); // Returns the ID referring to this shader in the GL.
        GLint status(); // Returns the status of compiling the shader.
        void attachTo(GLuint programId); // Attaches the shader to a GL program.
        void detachFrom(GLuint programId); // Detaches the shader from a GL program.
        std::string location();
    private:
        GLuint _handle;
        std::string _location;
        void logError(char const * location);
    };
}

#endif //GLFW_TEST_SHADER_H
