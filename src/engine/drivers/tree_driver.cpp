#include <string>
#include <iostream>
#include "Tree.h"

int main() {
    std::string path = "../../";
    std::cout << "Getting dir tree for " << path << std::endl;

    Engine::Tree* tree = new Engine::Tree();
    tree->fromPath(path);

    return 0;
}