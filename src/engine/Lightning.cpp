//
// Created by Christian Velez on 2/15/16.
//

#include "Lightning.h"

namespace Engine {
    Lightning::Lightning() {
        init();
    }

    Lightning::Lightning(GL::Program *program) {
        _program = program;
        init();
    }

    void Lightning::init() {
        // get light uniforms
        _uAmbientIntensity = _program->uniformLocation("dirLight.ambientIntensity");
        _uColor = _program->uniformLocation("dirLight.color");

        // set initial values
        _color = glm::vec3(1.0f, 1.0f, 1.0f);
        _intensity = 0.85f;
    }

    void Lightning::update() {
        // send color and intensity
        glUniform3f(_uColor, _color.x, _color.y, _color.z);
        glUniform1f(_uAmbientIntensity, _intensity);
    }
}