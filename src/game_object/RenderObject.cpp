//
// Created by Christian Velez on 2/7/16.
//

#include "RenderObject.h"

unsigned int RenderObject::_textureUnits;

RenderObject::RenderObject() {
    // create vao
    glGenVertexArrays(1, &_vao);
    showGLError("Generating vertex array");

    // create vbo
    glGenBuffers(1, &_vbo);
    showGLError("Generating vertex buffer");

    _program = NULL;
}

void RenderObject::addTexture(std::string path) {
    // create tex
    glGenTextures(1, &_texture);
    showGLError("Generating Texture");

    // set unit texture
    _tunit = RenderObject::_textureUnits;
    printf("Loading texture unit %i for image %s\n", _tunit, path.c_str());

    RenderObject::_textureUnits += 1;
    glActiveTexture(GL_TEXTURE0 + _tunit);
    showGLError("Setting texture unit");

    // bind and configure
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    showGLError("Binding and config Texture");


    // get texture image
    Util::SOILImage* img = Util::loadImage(path.c_str());
    if (img == NULL) {
        printf("Error loading texture \"%s\"\n", path.c_str());
    } else {
        printf("Buffered image %s to binded texture %u\n", path.c_str(), _texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->image);
        showGLError("Buffered Texture data");

        glGenerateMipmap(GL_TEXTURE_2D);
        showGLError("Generated Mipmaps");
        img->free();
    }
}

void RenderObject::move(glm::vec3 delta) {
    _trans = glm::translate(_trans, delta);
}

void RenderObject::showGLError(std::string errorName) {
    GLuint error = glGetError();
    if (error) printf("GLError - %s - %i\n", errorName.c_str(), error);
}
