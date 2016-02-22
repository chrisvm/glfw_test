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
        _objects = NULL;
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
            for (auto it = _programs->begin(); it != _programs->end(); ++it) {
                delete (*it).second;
            }
            delete _programs;
        }

        // delete objects
        if (_objects != NULL) {
            for (auto it = _objects->begin(); it != _objects->end(); ++it) {
                delete (*it).second;
            }
            delete _objects;
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

        // create objects cache
        _objects = new std::map<std::string, ObjFile*>();
    }

    void AssetLoader::processLocation() {
        std::thread *imgThread = NULL, *objThread = NULL;

        // get first level
        auto firstLevel = _tree->getChildren(0);
        for (auto it = firstLevel->begin(); it != firstLevel->end(); ++it) {
            int index = *it;
            NodePtr child = _tree->getNode(index);

            // if images
            if (child->name == "images" && child->is_dir) {
                // load images in other thread
                imgThread = new std::thread(loadImages, _tree, index, _images);
            } else if (child->name == "objects" && child->is_dir) {
                // load objects in other thread
                objThread = new std::thread(loadObjs, _tree, index, _objects);
            } else if (child->name == "shaders" && child->is_dir) {
                // load shader programs
                loadShaders(_tree, index, _programs);
            }
        }

        // join img and object loading threads
        if (imgThread != NULL) {
            imgThread->join();
        }
        if (objThread != NULL) {
            objThread->join();
        }
        delete imgThread;
    }

    Util::SOILImage *AssetLoader::getImage(std::string key) {
        return _images->at(key);
    }

    GL::Program* AssetLoader::getProgram(std::string key) {
        return _programs->at(key);
    }

    ObjFile *AssetLoader::getObjectFile(std::string key) {
        return _objects->at(key);
    }
}