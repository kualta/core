#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essential.h"
#include "ModelImporter.h"
#include "core/Modules/BgfxMesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace core {

class Model {
public:
    Model(const string& file);
    ~Model();

    BgfxMesh* mesh;
    Shader* shader;
};

}

#endif //CORE_MODEL_H
