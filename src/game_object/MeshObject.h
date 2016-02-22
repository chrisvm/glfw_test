//
// Created by Christian Velez on 2/21/16.
//

#ifndef GLFW_TEST_MESHOBJECT_H
#define GLFW_TEST_MESHOBJECT_H
#include "RenderObject.h"

namespace Engine {
    class Game;
    class ObjFile;
}

class MeshObject : public RenderObject {
    Engine::ObjFile* _file;

public:
    MeshObject(Engine::ObjFile* file, GL::Program* program, Engine::Game* game);
    virtual void configureProgram(GL::Program *program);
    virtual void bufferVertexData();
    virtual void render();
};


#endif //GLFW_TEST_MESHOBJECT_H
