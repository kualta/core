#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essentials.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

namespace core {

class Model {
public:
    Model(const shared<Mesh>& mesh, const shared<Shader>& shader);

    void Draw(Matrix4 &transformMtx, Camera &camera);

protected:

    Color3         color;
    shared<Mesh>   mesh;
    shared<Shader> shader;

};

} // namespace core

#endif //CORE_MODEL_H
