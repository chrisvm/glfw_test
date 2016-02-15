//
// Created by Christian Velez on 2/14/16.
//

#ifndef GLFW_TEST_ASSETLOADER_H
#define GLFW_TEST_ASSETLOADER_H
#include <string>
#include <map>
#include "tinydir.h"

namespace Engine {
    class AssetLoader {
        std::string _location;
        void processLocation();

    public:
        AssetLoader();
        void setLocation(std::string loc);
    };
}

#endif //GLFW_TEST_ASSETLOADER_H
