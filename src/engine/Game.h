//
// Created by Christian Velez on 2/14/16.
//

#ifndef GLFW_TEST_GAME_H
#define GLFW_TEST_GAME_H
#include <string>
#include "AssetLoader.h"

namespace Engine {
    class Game {
        AssetLoader* _loader;
        std::string _assetLoc;

    public:
        Game();
        ~Game();
        void init();
        void setAssetLocation(std::string location);
        AssetLoader* loader();
    };
}

#endif //GLFW_TEST_GAME_H
