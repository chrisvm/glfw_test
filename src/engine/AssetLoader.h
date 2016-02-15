//
// Created by Christian Velez on 2/14/16.
//

#ifndef GLFW_TEST_ASSETLOADER_H
#define GLFW_TEST_ASSETLOADER_H
#include <string>
#include <map>
#include <thread>
#include <cstring>
#include "tinydir.h"
#include "../util.h"


namespace Engine {
    class AssetLoader {
        std::string _location;
        std::map<std::string, Util::SOILImage>* _images;
        void processLocation();

    public:
        AssetLoader();
        void setLocation(std::string loc);
    };
}

#endif //GLFW_TEST_ASSETLOADER_H
