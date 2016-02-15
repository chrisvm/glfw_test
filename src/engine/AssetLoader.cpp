#include "AssetLoader.h"

namespace Engine {

    AssetLoader::AssetLoader() {
        _images = NULL;
        _programs = NULL;
        _tree = NULL;
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

    void loadShaders(Tree* tree, int root, std::map<std::string, GL::Program*> *_programs) {
        NodePtr rootNode = tree->getNode(root);
        auto children = tree->getChildren(root);

        // set to replace rootNode path
        std::regex rootPath(rootNode->path + "/"),
                fragShader("^[a-zA-Z_0-9]+\\.frag$"), vertShader("^[a-zA-Z_0-9]+\\.vert$");
        for (auto it = children->begin(); it != children->end(); ++it) {
            int current = (*it);
            NodePtr currentNode = tree->getNode(current);

            // if is dir
            if (currentNode->is_dir) {
                std::string programKey =
                        (std::string)std::regex_replace(
                                currentNode->path.c_str(), (std::basic_regex<char>)rootPath, "");
                printf("Creating Program %s\n", programKey.c_str());
                auto programFiles = tree->getChildren(current);

                GL::Shader *fs = NULL, *vs = NULL;
                for (auto pfiles = programFiles->begin(); pfiles != programFiles->end(); ++pfiles) {
                    NodePtr aFile = tree->getNode(*pfiles);

                    if (std::regex_match(aFile->name.c_str(), fragShader)) {
                        printf("Adding frag shader \"%s\" to %s\n", aFile->name.c_str(), programKey.c_str());
                        fs = new GL::Shader(GL_FRAGMENT_SHADER, aFile->path.c_str());
                    } else if (std::regex_match(aFile->name.c_str(), vertShader)) {
                        printf("Adding vert shader \"%s\" to %s\n", aFile->name.c_str(), programKey.c_str());
                        vs = new GL::Shader(GL_VERTEX_SHADER, aFile->path.c_str());
                    }
                }

                // create program if shaders found
                if (fs != NULL || vs != NULL) {
                    GL::Program *tProg = new GL::Program();
                    if (fs != NULL) {
                        tProg->attachShader(fs);
                    }
                    if (vs != NULL) {
                        tProg->attachShader(vs);
                    }
                    tProg->link();
                    (*_programs)[programKey] = tProg;
                } else {
                    printf("Program \"%s\" was empty, ignoring\n", programKey.c_str());
                }
            }
        }
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
                imgThread = new std::thread(loadImages, _tree, index, _images);
            } else if (child->name == "shaders" && child->is_dir) {
                // load shader programs
                loadShaders(_tree, index, _programs);
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

    GL::Program* AssetLoader::getProgram(std::string key) {
        return _programs->at(key);
    }
}