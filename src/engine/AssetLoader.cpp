#include "AssetLoader.h"

namespace Engine {

    AssetLoader::AssetLoader() {
        init();
    }

    AssetLoader::AssetLoader(Game* game) {
        init();
        _game = game;
    }

    void AssetLoader::init() {
        _images = NULL;
        _programs = NULL;
        _tree = NULL;
        _game = NULL;
    }
    void AssetLoader::clear() {
        // delete images
        if (_images != NULL) {
            for (auto it = _images->begin(); it != _images->end(); ++it) {
                (*it).second->free();
            }
            delete _images;
        }

        // delete tree
        if (_tree != NULL) {
            delete _tree;
        }

        // delete shaders
        if (_programs != NULL) {
            delete _programs;
        }
    }

    AssetLoader::~AssetLoader() {
        clear();
    }

    void AssetLoader::setLocation(std::string loc) {
        _location = loc;
        createCaches();
        processLocation();
    }


    void AssetLoader::createCaches() {
        // delete old caches
        clear();

        // create tree
        _tree = new Tree();
        _tree->fromPath(_location);

        // create images cache
        _images = new std::map<std::string, Util::SOILImage*>();

        // create shaders cache
        _programs = new std::map<std::string, GL::Program*>();
    }

    void AssetLoader::processLocation() {
        std::thread* imgThread = NULL;

        // get first level
        auto firstLevel = _tree->getChildren(0);
        for (auto it = firstLevel->begin(); it != firstLevel->end(); ++it) {
            int index = *it;
            NodePtr child = _tree->getNode(index);

            // if images
            if (child->name == "images" && child->is_dir) {
                // load images in other thread
                imgThread = new std::thread(loadImages, _tree, index, _images, _game);
            } else if (child->name == "shaders" && child->is_dir) {
                // load shader programs
                loadShaders(_tree, index, _programs, _game);
            }
        }

        // join img loading thread
        if (imgThread != NULL) {
            imgThread->join();
        }
        delete imgThread;
    }

    Util::SOILImage *AssetLoader::getImage(std::string key) {
        return _images->at(key);
    }

    GL::Program* AssetLoader::getProgram(std::string key) {
        return _programs->at(key);
    }
}