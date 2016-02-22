//
// Created by Christian Velez on 2/21/16.
//
#include "ObjFile.h"

namespace Engine {
    ObjFile::ObjFile() {

    }

    ObjFile::~ObjFile() {
        for (auto it = faces.begin(); it != faces.end(); ++it) {
            delete[] (*it);
        }
    }

    void ObjFile::openObj(std::string path) {
        // get file as vector of strings
        std::vector<std::string> lines = ObjFile::getFileAsLines(path);

        // for each line
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            // skip if comment
            if ((*it)[0] == '#') continue;

            // create stream from line
            std::stringstream ss(*it);
            std::string temp;
            ss >> temp;

            // mtllib
            if (temp == "mtllib") {
                ss >> materialsFile;
                continue;
            }

            // object
            if (temp == "o") {
                ss >> objectName;
                continue;
            }

            // material name
            if (temp == "usemtl") {
                ss >> materialName;
                continue;
            }

            // s?
            if (temp == "s") {
                ss >> s;
                continue;
            }

            // vector
            if (temp == "v") {
                glm::vec3 v;
                ss >> v.x >> v.y >> v.z;
                verts.push_back(v);
                continue;
            }

            // texture uv
            if (temp == "vt") {
                glm::vec2 uv;
                ss >> uv.x >> uv.y;
                uvs.push_back(uv);
                continue;
            }

            // normal
            if (temp == "vn") {
                glm::vec3 vn;
                ss >> vn.x >> vn.y >> vn.z;
                normals.push_back(vn);
                continue;
            }

            // faces
            if (temp == "f") {
                for (int x = 0; x < 3; ++x) {
                    int* face = new int[3];
                    ss >> face[0];
                    ss.get();
                    ss >> face[1];
                    ss.get();
                    ss >> face[2];

                    faces.push_back(face);
                }
                continue;
            }
        }
    }

    void ObjFile::openMtl(std::string path) {

    }

    std::vector<std::string> ObjFile::getFileAsLines(std::string path) {
        // open file
        std::ifstream infile(path);

        // get all lines
        std::vector<std::string> ret;
        std::string temp;
        while (infile.good()) {
            std::getline(infile, temp);
            ret.push_back(temp);
        }

        return ret;
    }

    void ObjFile::toFile(std::string path) {
        std::ofstream of(path);

        // print verts
        of << std::fixed;
        of << std::setprecision(6);
        for (auto it = verts.begin(); it != verts.end(); ++it) {
            of << "v " << (*it).x << " " << (*it).y << " " << (*it).z << std::endl;
        }

        // print uv
        for (auto it = uvs.begin(); it != uvs.end(); ++it) {
            of << "vt " << (*it).x << " " << (*it).y << std::endl;
        }
    }

    std::vector<GLfloat> ObjFile::joinedData() {
        std::vector<GLfloat> ret;

        // for all faces
        for (auto it = faces.begin(); it != faces.end(); ++it) {
            int* face = (*it);
            glm::vec3 v = verts[face[0] - 1];
            ret.push_back(v.x);
            ret.push_back(v.y);
            ret.push_back(v.z);
            glm::vec2 uv = uvs[face[1] - 1];
            ret.push_back(uv.x);
            ret.push_back(uv.y);
            glm::vec3 vn = normals[face[2] - 1];
            ret.push_back(vn.x);
            ret.push_back(vn.y);
            ret.push_back(vn.z);
        }

        return ret;
    }
}