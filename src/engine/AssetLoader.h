//
// Created by Christian Velez on 2/14/16.
//

#ifndef GLFW_TEST_ASSETLOADER_H
#define GLFW_TEST_ASSETLOADER_H
#include <string>
#include <map>
#include <thread>
#include <cstring>
#include <regex>
#include <queue>
#include "tinydir.h"
#include "Tree.h"
#include "../util.h"
#include "../gl/GLProgram.h"
#include "../gl/GLShader.h"


namespace Engine {
    class AssetLoader {
        std::string _location;
        std::map<std::string, Util::SOILImage*> *_images;
        std::map<std::string, GL::Program*> *_programs;
        Tree* _tree;

        void processLocation();
        void createCaches();
        void clear();

    public:
        AssetLoader();
        ~AssetLoader();

        void setLocation(std::string loc);
        Util::SOILImage* getImage(std::string key);
        GL::Program* getProgram(std::string key);
    };
}

#endif //GLFW_TEST_ASSETLOADER_H
