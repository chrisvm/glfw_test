#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include "../Tree.h"

std::string printList(std::list<int> *list);

int main() {
    std::string path = "assets";
    std::cout << "Getting dir tree for " << path << std::endl;

    Engine::Tree* tree = new Engine::Tree();
    tree->fromPath(path);

    for (int x = 0; x < tree->count(); ++x) {
        std::cout << x << " -> " << tree->getNode(x)->print() << std::endl;
    }

    std::cout << std::string(80, '-') << std::endl;

    for (int x = 0; x < tree->count(); ++x) {
        std::cout << x << " -> " << printList(tree->getChildren(x)) << std::endl;
    }
    return 0;
}

std::string printList(std::list<int> *list) {
    if (list->empty())
        return "[]";
    std::stringstream ss;
    ss << "[";
    auto it = list->begin();
    ss << *it;
    ++it;
    for (; it != list->end(); ++it)
        ss << ", " << *it;
    ss << "]";
    return ss.str();
}