//
// Created by Christian Velez on 2/7/16.
//

#ifndef GLFW_TEST_GAMEOBJECT_H
#define GLFW_TEST_GAMEOBJECT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "../gl/GLProgram.h"
#include "../util.h"
#include <list>
#include <string>


class RenderObject {
protected:
    glm::mat4 _trans;
    GLuint _vao, _vbo, _ebo, _texture, _tunit;
    GL::Program *_program;
    bool _usingElements;
    void showGLError(std::string errorName);

public:
    static unsigned int _textureUnits;

    RenderObject();
    void addTexture(std::string path);
    void move(glm::vec3 delta);
    void useElements();

    virtual void bufferVertexData() =0;
    virtual void bufferElementData();
    virtual void configureProgram(GL::Program *program) =0;
    virtual void render() =0;
};


#endif //GLFW_TEST_GAMEOBJECT_H
