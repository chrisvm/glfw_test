//
// Created by Christian Velez on 2/8/16.
//

#include "CubeObject.h"

CubeObject::CubeObject(GL::Program *program, Engine::Game* game): RenderObject(game) {

    // buffer cube data
    bufferVertexData();
    bufferElementData();

    // configure program
    configureProgram(program);
}

void CubeObject::configureProgram(GL::Program *program) {
    assert(_program == NULL);

    // describe vertex
    program->setVertexAttrib("position", 3, GL_FLOAT, 5, 0);
    program->setVertexAttrib("texcoord", 2, GL_FLOAT, 5, 3);
    showGLError("Setting vertex attributes");
    _program = program;
}

void CubeObject::bufferVertexData() {
    // bind vertex and buffer
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    showGLError("Bind Vertex Buffer and Array");

    if (_vertices == NULL) {
        // cube vertex data
        // composition: posx, posy, posz, txcoordx, txcoordy
        GLfloat vertices[] = {
                // front face
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

                // back face
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

                // left face
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                // right face
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                // bottom face
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

                // top face
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        };
        _vertices = new std::vector<GLfloat>(vertices, vertices + sizeof(vertices) / sizeof(GLfloat));
    }

    glBufferData(GL_ARRAY_BUFFER, _vertices->size() * sizeof(GLfloat), &(*_vertices)[0], GL_STATIC_DRAW);
    showGLError("Buffering vertex data");
}

void CubeObject::render() {
    // set context
    glBindVertexArray(_vao);
    showGLError("bind vertex array");

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
        glDrawElements(GL_TRIANGLES, (GLsizei)_elements->size(), GL_UNSIGNED_SHORT, (void*) 0);
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
            1, 2, 3,

            4, 5, 6,
            5, 6, 7,

            8, 9, 10,
            9, 10, 11,

            12, 13, 14,
            13, 14, 15,

            16, 17, 18,
            17, 18, 19,

            20, 21, 22,
            21, 22, 23
    };
    _elements = new std::vector<GLushort>(elements, elements + sizeof(elements) / sizeof(GLushort));

    // buffer element data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elements->size() * sizeof(unsigned short), &(*_elements)[0], GL_STATIC_DRAW);
    showGLError("Buffering elements");
}
