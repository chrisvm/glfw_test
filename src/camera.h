//
// Created by Christian Velez on 1/30/16.
//

#ifndef GLFW_TEST_CAMERA_H
#define GLFW_TEST_CAMERA_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "callbacks.h"

namespace Camera {
    class Camera {
        void configure();
        glm::mat4 viewTrans, projTrans;

    public:
        glm::vec3 pos;
        glm::vec2 rot;
        glm::vec2 last_mouse;
        glm::vec3 i, j, k;

        GLint viewUniform, projUniform;
        float camSpeed;
        float mouseSpeed;

        Camera(GLint viewUniform, GLint projUniform);
        void lookAt(glm::vec3 point);
        void FPSCam(float deltaTime);
        void update();
    };
}

#endif //GLFW_TEST_CAMERA_H
