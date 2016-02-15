//
// Created by Christian Velez on 2/8/16.
//

#ifndef GLFW_TEST_CUBEOBJECT_H
#define GLFW_TEST_CUBEOBJECT_H
#include "RenderObject.h"
#include "../engine/Game.h"
#include <vector>

class CubeObject : public RenderObject {

public:
    CubeObject(GL::Program *program, Engine::Game* game);
    virtual void configureProgram(GL::Program *program);
    virtual void bufferVertexData();
    virtual void bufferElementData();
    virtual void render();
};


#endif //GLFW_TEST_CUBEOBJECT_H
