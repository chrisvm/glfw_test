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
#include <list>


class RenderObject {
protected:
    glm::mat4 _trans;
    GLuint _vao, _vbo;
    std::list<GLuint> _textures;
    GL::Program *_program;

public:
    RenderObject();
    virtual void bufferVertexData() =0;
    virtual void configureProgram(GL::Program *program) =0;
};


#endif //GLFW_TEST_GAMEOBJECT_H
