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
#include "../engine/Game.h"
#include "../util.h"
#include <list>
#include <string>
#include <vector>


class RenderObject {
    void _init();

protected:
    glm::mat4 _trans;
    GLuint _vao, _vbo, _ebo, _texture, _tunit;
    GL::Program *_program;
    std::vector<GLushort> * _elements;
    std::vector<GLfloat> * _vertices;
    Engine::Game* _game;

    bool _usingElements;
    void showGLError(std::string errorName);

public:
    static unsigned int _textureUnits;

    RenderObject();
    RenderObject(Engine::Game* game);
    void addTexture(std::string path);
    void move(glm::vec3 delta);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 scale);
    void scale(float scale);
    void useElements();

    virtual void bufferVertexData() =0;
    virtual void bufferElementData();
    virtual void configureProgram(GL::Program *program) =0;
    virtual void render() =0;
};


#endif //GLFW_TEST_GAMEOBJECT_H
