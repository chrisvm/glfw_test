//
// Created by Christian Velez on 2/7/16.
//

#include "GLProgram.h"

namespace GL {
    Program::Program() {
        init();
    }

    void Program::init() {
        _program = glCreateProgram();
    }

    void Program::attachShader(Shader *shader) {
        attachShader(shader->location(), shader);
    }

    void Program::attachShader(std::string shaderName, Shader *shader) {
        ShaderNode t;
        t.name = shaderName;
        t.shader = shader;
        shader->attachTo(_program);
        _shaders.push_back(t);
    }

    void Program::link() {
        glLinkProgram(_program);
    }

    void Program::use() {
        glUseProgram(_program);
    }

    GLuint Program::id() {
        return _program;
    }

    GLint Program::uniformLocation(std::string location) {
        return glGetUniformLocation(_program, location.c_str());
    }

    GLint Program::attribLocation(std::string location) {
        return glGetAttribLocation(_program, location.c_str());
    }

    void Program::setVertexAttrib(std::string location, GLuint size, GLenum format, GLuint stride, GLuint index) {
        GLint attrib = attribLocation(location);
        GLint typeSize = getTypeSize(format);
        stride = stride * typeSize;
        index = index * typeSize;
        glEnableVertexAttribArray(attrib);
        glVertexAttribPointer(attrib, size, format, GL_FALSE, stride, (void*)(long) index);
    }

    GLuint Program::getTypeSize(GLenum type) {
        if (type == GL_FLOAT)
            return sizeof(GLfloat);
        if (type == GL_INT)
            return sizeof(GLint);
        if (type == GL_DOUBLE)
            return sizeof(GLdouble);
        if (type == GL_UNSIGNED_SHORT)
            return sizeof(GLushort);
        return sizeof(GLint);
    }
}