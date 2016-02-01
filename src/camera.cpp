//
// Created by Christian Velez on 1/30/16.
//
#include "camera.h"

namespace Camera {
    Camera::Camera(GLint viewUniform, GLint projUniform) {
        this->viewUniform = viewUniform;
        this->projUniform = projUniform;

        this->configure();
    }

    void Camera::configure() {
        this->projTrans = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 1.0f, 10.0f);
        glUniformMatrix4fv(this->projUniform, 1, GL_FALSE, glm::value_ptr(this->projTrans));

        this->pos = glm::vec3(1.2f, 1.2f, 1.2f);
    }

    void Camera::lookAt(glm::vec3 point) {
        this->viewTrans = glm::lookAt(
                this->pos,
                point,
                glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }

    // TODO: fix this method
    void Camera::update() {
        this->viewTrans = glm::mat4();
        glm::translate(this->viewTrans, this->pos);
        glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(this->viewTrans));
    }
}
