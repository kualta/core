#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essential.h"
#include "ModelImporter.h"
#include "Shader.h"
#include "Mesh.h"

#include <Magnum/Math/Matrix4.h>

namespace core {

class Model {
public:
    Model(Mesh* _mesh, Shader* _shader);
    ~Model();

    void Draw();

protected:

    Magnum::Matrix4 transformMtx;
    Magnum::Matrix4 projectionMtx;
    Magnum::Color3  color;

    Mesh*   mesh;
    Shader* shader;
};

}

#endif //CORE_MODEL_H
