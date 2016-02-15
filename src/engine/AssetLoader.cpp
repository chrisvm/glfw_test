#include "AssetLoader.h"

namespace Engine {

    AssetLoader::AssetLoader() {
        _images = NULL;
        _tree = NULL;
    }

    AssetLoader::~AssetLoader() {
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
    }

    void AssetLoader::setLocation(std::string loc) {
        _location = loc;
        createTree();
        processLocation();
    }

    void loadImages(Tree* tree, int root, std::map<std::string, Util::SOILImage*>* imgs) {
        NodePtr _root = tree->getNode(root);
        printf("image loading from \"%s\"\n", _root->name.c_str());

        // set to replace _root path
        std::regex rootPath(_root->path + "/");
        std::queue<int> nodeQueue;

        // start bfs
        nodeQueue.push(root);
        while (!nodeQueue.empty()) {
            // get current node
            int current = nodeQueue.front();

            // check if dir
            NodePtr currentNode = tree->getNode(current);
            if (currentNode->is_dir) {
                // pop current
                nodeQueue.pop();

                // get children count
                long count = tree->getChildren(current)->size();
                // if has children
                if (count > 0) {
                    auto children = tree->getChildren(current);
                    for (auto it = children->begin(); it != children->end(); ++it) {
                        nodeQueue.push(*it);
                    }
                }
                continue;
            }

            // remove rootPath
            std::string key =
                    (std::string)std::regex_replace(currentNode->path.c_str(), (std::basic_regex<char>)rootPath, "");

            // get texture image
            Util::SOILImage* img = Util::loadImage(currentNode->path.c_str());
            (*imgs)[key] = img;

            // remove current
            nodeQueue.pop();
        }
    }

    void AssetLoader::createTree() {
        // delete old tree
        if (_tree != NULL) {
            delete _tree;
        }

        // create tree
        _tree = new Tree();
        _tree->fromPath(_location);
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
                // create image cache
                _images = new std::map<std::string, Util::SOILImage*>();

                // load images in other thread
                imgThread = new std::thread(loadImages, _tree, index, _images);
            } else if (child->name == "shaders" && child->is_dir) {
                // load shader programs

            }
        }

        // join img loading thread
        if (imgThread != NULL) {
            imgThread->join();
        }
    }

    Util::SOILImage *AssetLoader::getImage(std::string key) {
        return _images->at(key);
    }
}