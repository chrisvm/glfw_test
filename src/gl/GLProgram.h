//
// Created by Christian Velez on 2/7/16.
//

#ifndef GLFW_TEST_GLPROGRAM_H
#define GLFW_TEST_GLPROGRAM_H
#include <GL/glew.h>
#include <string>
#include <list>
#include "GLShader.h"


namespace GL {
    struct ShaderNode {
        std::string name;
        Shader *shader;
    };

    class Program {
        GLuint _program;
        std::list<ShaderNode> _shaders;
        GLuint getTypeSize(GLenum type);

    public:
        Program();
        void attachShader(Shader * shader);
        void attachShader(std::string shaderName, Shader* shader);
        void link();
        void use();
        GLuint id();
        GLint uniformLocation(std::string location);
        GLint attribLocation(std::string location);
        void setVertexAttrib(std::string location, GLuint size, GLenum format, GLuint stride, GLuint index);
    };
}

#endif //GLFW_TEST_GLPROGRAM_H
