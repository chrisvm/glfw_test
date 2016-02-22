//
// Created by Christian Velez on 2/15/16.
//

#include "loaders.h"

namespace Engine {

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
                // get program key
                std::string programKey =
                        (std::string)std::regex_replace(
                                currentNode->path.c_str(), (std::basic_regex<char>)rootPath, "");
                printf("Creating Program %s\n", programKey.c_str());
                auto programFiles = tree->getChildren(current);

                GL::Shader *fs = NULL, *vs = NULL;
                // get all folder's children
                for (auto pfiles = programFiles->begin(); pfiles != programFiles->end(); ++pfiles) {
                    NodePtr aFile = tree->getNode(*pfiles);

                    // check for type of file
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

    void loadObjs(Tree* tree, int root, std::map<std::string, ObjFile*> *_objects) {
        // get root node
        NodePtr rootNode = tree->getNode(root);
        printf("Opening dir \"%s\"\n", rootNode->name.c_str());

        // file name regex
        std::regex mtlReg("^[a-zA-Z_0-9]+\\.mtl$"),
                objReg("^[a-zA-Z_0-9]+\\.obj$"),
                rootPath(rootNode->path + "/");

        // iterate tree
        auto children = tree->getChildren(root);
        for (auto it = children->begin(); it != children->end(); ++it) {
            int current = (*it);
            NodePtr currentNode = tree->getNode(current);

            // if dir found, check
            if (currentNode->is_dir) {
                // remove asset path
                std::string objectKey = (std::string)std::regex_replace(
                        currentNode->path.c_str(), (std::basic_regex<char>)rootPath, "");

                // get files inside dir
                auto objectFiles = tree->getChildren(current);
                printf("Scanning object \"%s\"\n", objectKey.c_str());
                int foundObj = -1, foundMtl = -1;

                // iterate all files inside dir looking for .obj files
                for (auto oFiles = objectFiles->begin(); oFiles != objectFiles->end(); ++oFiles) {
                    NodePtr oFile = tree->getNode(*oFiles);
                    if (std::regex_match(oFile->name.c_str(), objReg)) {
                        foundObj = (*oFiles);
                    } else if (std::regex_match(oFile->name.c_str(), mtlReg)) {
                        foundMtl = (*oFiles);
                    }
                }

                // if found obj
                if (foundObj != -1) {
                    // create new obj
                    ObjFile *objectFile = new ObjFile();
                    objectFile->openObj(tree->getNode(foundObj)->path);

                    // if mtl found, open
                    if (foundMtl != -1) {
                        objectFile->openMtl(tree->getNode(foundMtl)->path);
                    }

                    // add to objects cache
                    printf("Added object \"%s\" to loader\n", objectKey.c_str());
                    (*_objects)[objectKey] = objectFile;
                }
            }
        }
    }
}