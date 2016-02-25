//
// Created by Christian Velez on 1/30/16.
//
#include "camera.h"

namespace Camera {
    Camera::Camera(GLint viewUniform, GLint projUniform, GLint eyeUniform) {
        this->viewUniform = viewUniform;
        this->projUniform = projUniform;
        this->eyeUniform = eyeUniform;
        this->camSpeed = 2.0;
        this->mouseSpeed = 0.10;

        this->configure();
    }

    void Camera::configure() {

        // set the projection transform
        glm::vec2 winSize = Callbacks::getWindowSize();
        this->projTrans = glm::perspectiveFov(glm::radians(80.0f), winSize.x, winSize.y, 1.0f, 10.0f);
        glUniformMatrix4fv(this->projUniform, 1, GL_FALSE, glm::value_ptr(this->projTrans));

        // init all vectors
        pos = glm::vec3(4.0f, 0.0f, 1.0f);
        last_mouse = Callbacks::getMouse();
        halfPI = 3.14f / 2.0f;
        rot = glm::vec2(-halfPI, 0.0f);
        i = glm::vec3(1.0f, 0.0f, 0.0f);
        j = glm::vec3(0.0f, 1.0f, 0.0f);
        k = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    void Camera::lookAt(glm::vec3 point) {
        viewTrans = glm::lookAt(
                pos,
                point,
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewTrans));
    }

    void Camera::FPSCam(float deltaTime) {
        // update mouse
        glm::vec2 mouse = Callbacks::getMouse();

        // add  mouse delta
        rot += - mouseSpeed * deltaTime * (mouse - last_mouse);
        last_mouse = mouse;

        // clamp the vertical angle
        if (rot.y > halfPI) rot.y = halfPI;
        if (rot.y < -halfPI) rot.y = -halfPI;

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

        viewTrans = glm::lookAt(
                pos,
                pos + direction,
                up
        );
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
        glUniform3f(this->eyeUniform, pos.x, pos.y, pos.z);
    }

    // TODO: fix this method
    void Camera::update() {
        this->viewTrans = glm::mat4();
        glm::translate(this->viewTrans, this->pos);
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }
}
