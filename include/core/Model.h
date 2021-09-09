#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essential.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

namespace core {

class Model {
public:
    Model(Mesh* _mesh, Shader* _shader);
    ~Model();

    void Draw();

protected:

    Matrix4 transformMtx;
    Matrix4 projectionMtx;
    Color3  color;

    Mesh*   mesh;
    Shader* shader;
};

}

#endif //CORE_MODEL_H
