//
// Created by Christian Velez on 2/14/16.
//

#include "AssetLoader.h"
#include "tinydir.h"

namespace Engine {
    AssetLoader::AssetLoader() {
        _images = NULL;
    }

    void AssetLoader::setLocation(std::string loc) {
        _location = loc;
        processLocation();
    }

    void loadImages(std::string path, std::map<std::string, Util::SOILImage>* _imgs) {
//        // open dir
//        tinydir_dir dir;
//        tinydir_open(&dir, path.c_str());
//
//        while (dir.has_next) {
//            tinydir_file file;
//            tinydir_readfile(&dir, &file);
//
//            // ignore "." and ".."
//            if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
//                continue;
//
//            printf("Path: %s\nName: %s\nExtension: %s\nIs dir? %s\nIs regular file? %s\n",
//                   file.path, file.name, file.extension,
//                   file.is_dir?"yes":"no", file.is_reg?"yes":"no");
//
//            tinydir_next(&dir);
//        }
//
//        tinydir_close(&dir);
    }

    void AssetLoader::processLocation() {
        // open dir
        tinydir_dir dir;
        tinydir_open(&dir, _location.c_str());

        std::thread* imgThread = NULL;

        while (dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);

            // ignore "." and ".."
            if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
                continue;

            if (strcmp(file.name, "images") == 0) {
                // load images
                std::string imgsPath = _location + "/" + std::string(file.name);
                printf("AssetLoader:: Loading images in background from %s\n", imgsPath.c_str());

                // start thread
                //imgThread = new std::thread(loadImages, imgsPath, _images);

            } else if (strcmp(file.name, "shaders") == 0) {
                // load shaders
                printf("AssetLoader:: Loading shaders in %s\n", file.name);
            }
            tinydir_next(&dir);
        }
        if (imgThread != NULL)
            imgThread->join();
        tinydir_close(&dir);
    }
}