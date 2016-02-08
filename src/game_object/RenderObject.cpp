//
// Created by Christian Velez on 2/7/16.
//

#include "RenderObject.h"

RenderObject::RenderObject() {
    // create vao
    glGenVertexArrays(1, &_vao);

    // create vbo
    glGenBuffers(1, &_vbo);

    _program = NULL;
}
