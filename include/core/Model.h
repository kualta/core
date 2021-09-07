#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essential.h"
#include "ModelImporter.h"
#include "Shader.h"
#include "Mesh.h"

namespace core {

class Model {
public:
    Model(const string& file);
    ~Model();

    Mesh* mesh;
    Shader* shader;
};

}

#endif //CORE_MODEL_H
