//
// Created by Christian Velez on 2/8/16.
//

#ifndef GLFW_TEST_CUBEOBJECT_H
#define GLFW_TEST_CUBEOBJECT_H
#include "RenderObject.h"

class CubeObject : RenderObject {
public:
    CubeObject(GL::Program *program);
    virtual void configureProgram(GL::Program *program);
    virtual void bufferVertexData();
};


#endif //GLFW_TEST_CUBEOBJECT_H
