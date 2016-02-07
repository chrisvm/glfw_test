//
// Created by Christian Velez on 1/30/16.
//
#include "camera.h"

namespace Camera {
    Camera::Camera(GLint viewUniform, GLint projUniform) {
        this->viewUniform = viewUniform;
        this->projUniform = projUniform;
        this->camSpeed = 2.0;
        this->mouseSpeed = 0.10;

        this->configure();
    }

    void Camera::configure() {
        glm::vec2 winSize = Callbacks::getWindowSize();
        this->projTrans = glm::perspectiveFov(glm::radians(70.0f), winSize.x, winSize.y, 1.0f, 10.0f);
        glUniformMatrix4fv(this->projUniform, 1, GL_FALSE, glm::value_ptr(this->projTrans));

        this->pos = glm::vec3(1.2f, 1.2f, 1.2f);
        this->rot = glm::vec2(3.14f   , 0.0);
        this->last_mouse = Callbacks::getMouse();
        i = glm::vec3(1.0f, 0.0f, 0.0f);
        j = glm::vec3(0.0f, 1.0f, 0.0f);
        k = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    void Camera::lookAt(glm::vec3 point) {
        this->viewTrans = glm::lookAt(
                this->pos,
                point,
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }

    void Camera::FPSCam(float deltaTime) {
        // update mouse
        glm::vec2 mouse = Callbacks::getMouse();

        // add  mouse delta
        rot += mouseSpeed * deltaTime * - (mouse - last_mouse);
        float halfPi = 3.14f / 2.0;

        // clamp the vertical angle
        if (rot.y > halfPi) rot.y = halfPi;
        if (rot.y < -halfPi) rot.y = -halfPi;
        last_mouse = mouse;

        glm::vec3 direction(
                cos(rot.y) * sin(rot.x),
                sin(rot.y),
                cos(rot.y) * cos(rot.x)
        );

        glm::vec3 right = glm::vec3(
                sin(rot.x - 3.14f/2.0f),
                0,
                cos(rot.x - 3.14f/2.0f)
        );

        glm::vec3 up = glm::cross(right, direction);

        // check key presses
        if (Callbacks::getKey(GLFW_KEY_A)) {
            pos += -right * deltaTime * camSpeed;
        }
        if (Callbacks::getKey(GLFW_KEY_D)) {
            pos +=  right * deltaTime * camSpeed;
        }
        if (Callbacks::getKey(GLFW_KEY_W)) {
            pos += direction * deltaTime * camSpeed;
        }
        if (Callbacks::getKey(GLFW_KEY_S)) {
            pos += -direction * deltaTime * camSpeed;
        }


        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }

    // TODO: fix this method
    void Camera::update() {
        this->viewTrans = glm::mat4();
        glm::translate(this->viewTrans, this->pos);
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }
}
