//
// Created by Christian Velez on 2/15/16.
//

#ifndef GLFW_TEST_TREE_H
#define GLFW_TEST_TREE_H
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include "tinydir.h"

namespace Engine {

    struct Node {
        std::string name, path, extension;
        bool is_dir, is_reg;

        Node() {;}

        Node(tinydir_file* file) {
            this->name = std::string(file->name);
            this->path = std::string(file->path);
            this->extension = std::string(file->extension);
            this->is_dir = file->is_dir;
            this->is_reg = file->is_reg;
        }

        std::string print() {
            std::stringstream ss;
            ss << "Node {path: '" << this->path << "', name:'" << this->name << "', ";
            ss << "is_dir: '" << (this->is_dir ? "True" : "False") << "'}";
            return ss.str();
        }
    };

    typedef std::list<int>* IndexList;
    typedef Node* NodePtr;

    class Tree {
        std::vector<NodePtr> _nodes;
        std::vector<IndexList> _children;
        int _head;

        void r_tree_run(int root, const char * path);
        int add_node(int parent, NodePtr node);

    public:
        Tree();
        ~Tree();
        void fromPath(std::string path);
        void empty();
        int count();
        NodePtr getNode(int index);
        IndexList getChildren(int index);

    };
}

#endif //GLFW_TEST_TREE_H
