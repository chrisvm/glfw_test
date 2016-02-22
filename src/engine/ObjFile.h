//
// Created by Christian Velez on 2/21/16.
//

#ifndef GLFW_TEST_OBJFILE_H
#define GLFW_TEST_OBJFILE_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <GL/glew.h>


namespace Engine {
    struct ObjFile {
        std::vector<glm::vec3> verts;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<int*> faces;

        std::string materialsFile, materialName, objectName, s;

        ObjFile();
        ~ObjFile();
        void openObj(std::string path);
        void openMtl(std::string path);
        void toFile(std::string path);
        std::vector<GLfloat> joinedData();
        static std::vector<std::string> getFileAsLines(std::string path);
    };
}


#endif //GLFW_TEST_OBJFILE_H
