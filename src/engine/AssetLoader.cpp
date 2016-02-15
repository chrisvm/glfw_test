//
// Created by Christian Velez on 2/14/16.
//

#include "AssetLoader.h"

namespace Engine {
    AssetLoader::AssetLoader() {

    }

    void AssetLoader::setLocation(std::string loc) {
        _location = loc;
        processLocation();
    }

    void AssetLoader::processLocation() {
        // open dir
        tinydir_dir dir;
        tinydir_open(&dir, _location.c_str());

        while (dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if (file.name == "images") {
                // load images
                printf("AssetLoader:: Loading images in %s\n", file.name);
            } else if (file.name == "shaders") {
                // load shaders
                printf("AssetLoader:: Loading shaders in %s\n", file.name);
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
    }
}