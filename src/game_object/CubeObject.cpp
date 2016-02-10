//
// Created by Christian Velez on 2/8/16.
//

#include "CubeObject.h"

CubeObject::CubeObject(GL::Program *program) {
    // buffer cube data
    bufferVertexData();
    bufferElementData();

    // configure program
    configureProgram(program);
}

void CubeObject::configureProgram(GL::Program *program) {
    assert(_program == NULL);

    // describe vertex
    program->setVertexAttrib("position", 3, GL_FLOAT, 8, 0);
    program->setVertexAttrib("color", 3, GL_FLOAT, 8, 3);
    program->setVertexAttrib("texcoord", 2, GL_FLOAT, 8, 6);
    showGLError("Setting vertex attributes");
    _program = program;
}

void CubeObject::bufferVertexData() {
    // bind vertex and buffer
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    showGLError("Bind Vertex Buffer and Array");

    // buffer cube vertex data
    // composition: posx, posy, posz, rcolor, gcolor, bcolor, txcoordx, txcoordy
    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    showGLError("Buffering vertex data");
}

void CubeObject::render() {
    // set context
    glBindVertexArray(_vao);
    showGLError("bind vertex array");

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    showGLError("bind texture buffer");

    if (_usingElements) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        showGLError("Binding element buffer");
    }

    glActiveTexture(GL_TEXTURE0 + _tunit);
    showGLError("Set Active Texture");

    glBindTexture(GL_TEXTURE_2D, _texture);
    showGLError("bind texture");


    // set transform
    GLint uniformModelTransform = _program->uniformLocation("model");
    glUniformMatrix4fv(uniformModelTransform, 1, GL_FALSE, glm::value_ptr(_trans));
    showGLError("Uniform model transform");

    // set sampler unit
    GLint uniSampler = _program->uniformLocation("sampler");
    glUniform1i(uniSampler, _tunit);
    showGLError("Uniform sampler");

    // draw cube
    if (_usingElements) {
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void*) 0);
        showGLError("Rendering elements");
    } else {
        glDrawArrays(GL_TRIANGLES, 0, 36);
        showGLError("Drawing arrays");
    }
}

void CubeObject::bufferElementData() {
    RenderObject::bufferElementData();
    // set element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    // create vector with elements
    GLushort elements[] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            7, 8, 9
    };
    // buffer element data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements) * sizeof(unsigned short), &elements, GL_STATIC_DRAW);
    showGLError("Buffering elements");
}
