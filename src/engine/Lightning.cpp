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
        showGLError("uniform location ambient");

        _uDiffuseIntensity = _program->uniformLocation("dirLight.diffuseIntensity");
        _uDirection = _program->uniformLocation("dirLight.direction");
        showGLError("uniform location diffuse");

        _uSpecularIntensity = _program->uniformLocation("dirLight.specularIntensity");
        _uSpecularPower = _program->uniformLocation("dirLight.specularPower");
        showGLError("uniform location specular");

        // set initial values
        _color = glm::vec3(1.0f, 1.0f, 1.0f);
        _direction = glm::vec3(0.0f, -1.0f, 0.0f);
        _diff_intensity = 0.65f;
        _amb_intensity = 0.10f;
        _spec_intensity = 0.25f;
        _spec_power = 64;
    }

    void Lightning::update() {
        // send color and intensity
        glUniform3f(_uColor, _color.x, _color.y, _color.z);
        glUniform1f(_uAmbientIntensity, _amb_intensity);
        showGLError("uniform ambient light");

        // send diffuse props
        glUniform1f(_uDiffuseIntensity, _diff_intensity);
        glm::normalize(_direction);
        glUniform3f(_uDirection, _direction.x, _direction.y, _direction.z);
        showGLError("uniform diffuse light");

        // send specular props
        glUniform1f(_uSpecularIntensity, _spec_intensity);
        glUniform1f(_uSpecularPower, _spec_power);
    }

    void Lightning::showGLError(std::string errorName) {
        GLuint error = glGetError();
        if (error) printf("GLError - %s - %i\n", errorName.c_str(), error);
    }
}