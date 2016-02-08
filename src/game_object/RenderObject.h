//
// Created by Christian Velez on 2/7/16.
//

#ifndef GLFW_TEST_GAMEOBJECT_H
#define GLFW_TEST_GAMEOBJECT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class RenderObject {
    glm::mat4 _trans;
    GLuint _vao, _vbo;
public:
    RenderObject();

};


#endif //GLFW_TEST_GAMEOBJECT_H
