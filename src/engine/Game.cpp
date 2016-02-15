//
// Created by Christian Velez on 2/14/16.
//

#include "Game.h"
namespace Engine {
    Game::Game() {
        _loader = NULL;
    }

    Game::~Game() {
        if (_loader != NULL) {
            delete _loader;
        }
    }

    void Game::setAssetLocation(std::string location) {
        _assetLoc = location;
        if (_loader != NULL) {
            _loader->setLocation(_assetLoc);
        }
    }

    void Game::init() {
        // init asset loader
        if (_loader == NULL) {
            _loader = new Engine::AssetLoader();
            if (_assetLoc != "") {
                _loader->setLocation(_assetLoc);
            }
        }
    }

    AssetLoader* Game::loader() {
        return _loader;
    }
}