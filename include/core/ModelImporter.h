#ifndef CORE_MODELIMPORTER_H
#define CORE_MODELIMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace core {

class ModelImporter {
public:
    ModelImporter();

    static Assimp::Importer importer;


};

}

#endif //CORE_MODELIMPORTER_H
