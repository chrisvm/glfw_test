//
// Created by Christian Velez on 2/21/16.
//

#include "MeshObject.h"

MeshObject::MeshObject(Engine::ObjFile* file, GL::Program* program, Engine::Game* game): RenderObject(game) {
    _file = file;

    // buffer cube data
    bufferVertexData();
    configureProgram(program);
}

void MeshObject::configureProgram(GL::Program *program) {
    assert(_program == NULL);

    // describe vertex
    program->setVertexAttrib("position", 3, GL_FLOAT, 8, 0);
    program->setVertexAttrib("texcoord", 2, GL_FLOAT, 8, 3);
    program->setVertexAttrib("normal", 3, GL_FLOAT, 8, 5);
    showGLError("Setting vertex attributes");
    _program = program;
}

void MeshObject::bufferVertexData() {
    // bind vertex and buffer
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    showGLError("Bind Vertex Buffer and Array");

    // get joined buffer data
    std::vector<GLfloat> bufferData = _file->joinedData();

    // buffer data
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(GLfloat), &bufferData[0], GL_STATIC_DRAW);
    showGLError("Buffering vertex data");
}

void MeshObject::render() {
    // set context
    glBindVertexArray(_vao);
    showGLError("bind vertex array");

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

    // draw object
    glDrawArrays(GL_TRIANGLES, 0, (int)_file->faces.size() * 3);
    showGLError("Drawing arrays");
}