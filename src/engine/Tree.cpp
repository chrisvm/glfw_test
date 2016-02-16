//
// Created by Christian Velez on 2/15/16.
//

#include "Tree.h"
namespace Engine {
    Tree::Tree() {
        _head = -1;
    }

    Tree::~Tree() {
        empty();
    }

    void Tree::fromPath(std::string path) {
        // empty if loaded
        if (_nodes.size()) {
            empty();
        }

        // add root node to tree
        NodePtr _root = new Node();
        _root->is_dir = true;
        _root->name = std::string(path);
        int root = add_node(-1, _root);

        // recursive open dir
        r_tree_run(root, path.c_str());
    }

    void Tree::r_tree_run(int root, const char *path) {

        // open path
        tinydir_dir *dir = new tinydir_dir;
        tinydir_open(dir, path);

        // read all files
        tinydir_file *file = new tinydir_file;
        while (dir->has_next) {
            tinydir_readfile(dir, file);

            // ignore "." and ".."
            if (strcmp(file->name, ".") == 0 || strcmp(file->name, "..") == 0) {
                tinydir_next(dir);
                continue;
            }

            // create new node
            NodePtr tnode = new Node(file);
            int troot = add_node(root, tnode);

            // create subtree
            if (file->is_dir) {
                r_tree_run(troot, file->path);
            }

            // get next file
            tinydir_next(dir);
        }

        tinydir_close(dir);
        delete dir;
        delete file;
    }

    void Tree::empty() {
        // delete all nodes
        {
            for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
                delete *(it);
            }
            _nodes.clear();
        }

        // delete all children lists
        {
            for (auto it = _children.begin(); it != _children.end(); ++it) {
                delete *(it);
            }
            _nodes.clear();
        }
    }

    int Tree::add_node(int parent, NodePtr node) {
        // get size, is the index
        int ret = _nodes.size();
        _nodes.push_back(node);

        // create children list for node
        IndexList tlist = new std::list<int>;
        _children.push_back(tlist);

        // check if has parent
        if (parent != -1) {
            _children[parent]->push_back(ret);
        }

        return ret;
    }

    NodePtr Tree::getNode(int index) {
        return _nodes[index];
    }

    IndexList Tree::getChildren(int index) {
        return _children[index];
    }

    int Tree::count() {
        return _nodes.size();
    }
}