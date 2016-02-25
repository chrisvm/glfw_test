//
// Created by Christian Velez on 2/15/16.
//

#ifndef GLFW_TEST_LIGHTNING_H
#define GLFW_TEST_LIGHTNING_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../gl/GLProgram.h"

namespace Engine {
    class Lightning {
        GL::Program *_program;
        void init();
        GLint _uColor, _uAmbientIntensity, _uDiffuseIntensity, _uDirection;
        GLint _uSpecularIntensity, _uSpecularPower;
        glm::vec3 _color, _direction;
        GLfloat _amb_intensity, _diff_intensity;
        GLfloat _spec_intensity, _spec_power;
        void showGLError(std::string errorName);

    public:
        Lightning();
        Lightning(GL::Program *program);
        void update();
    };
}

#endif //GLFW_TEST_LIGHTNING_H
