//
// Created by Christian Velez on 2/15/16.
//

#ifndef GLFW_TEST_LOADERS_H
#define GLFW_TEST_LOADERS_H
#include <map>
#include <string>
#include <regex>
#include <queue>
#include "Tree.h"
#include "../util.h"
#include "../gl/GLProgram.h"
#include "../gl/GLShader.h"

namespace Engine {
    class Game;

    void loadImages(Tree* tree, int root, std::map<std::string, Util::SOILImage*>* imgs, Game* parent);
    void loadShaders(Tree* tree, int root, std::map<std::string, GL::Program*> *_programs, Game* parent);
}

#endif //GLFW_TEST_LOADERS_H
