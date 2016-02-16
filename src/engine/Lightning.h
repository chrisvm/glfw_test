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
        GLint _uColor, _uAmbientIntensity;
        glm::vec3 _color;
        GLfloat _intensity;

    public:
        Lightning();
        Lightning(GL::Program *program);
        void update();
    };
}

#endif //GLFW_TEST_LIGHTNING_H
