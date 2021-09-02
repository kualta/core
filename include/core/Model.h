#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essential.h"
#include "ModelImporter.h"
#include "Shader.h"
#include "core/Modules/IRendererMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace core {

class Model {
public:
    Model(const string& file);
    ~Model();

    IRendererMesh* mesh;
    Shader* shader;
};

}

#endif //CORE_MODEL_H
