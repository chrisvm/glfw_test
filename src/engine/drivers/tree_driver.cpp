#include <string>
#include <iostream>
#include "../Tree.h"

int main() {
    std::string path = "../../";
    std::cout << "Getting dir tree for " << path << std::endl;

    Engine::Tree* tree = new Engine::Tree();
    tree->fromPath(path);

    for (int x = 0; x < tree->count(); ++x) {
        std::cout << x << " -> " << tree->getNode(x)->print() << std::endl;
    }

    return 0;
}