#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essentials.h"
#include "IDrawable.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

#include "core/Components/Light.h"
#include <core/Components/Camera.h>
#include <core/Components/Transform.h>

namespace core {

class Model : public IDrawable {
public:
    Model(const shared<Mesh>& mesh, const shared<Shader>& shader);

    static vector<shared<Model>> Load(const string& filepath);

    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;
    void SetNormalMatrix(Matrix4& mtx);
    void SetDiffuseColor(Color3& color);
    void SetLightColor(Light& light);

protected:
    friend class Renderer;

    void Draw();

    Color3         color;
    shared<Mesh>   mesh;
    shared<Shader> shader;

    GL::Buffer transformUniform;
    GL::Buffer projectionUniform;
    GL::Buffer materialUniform;
    GL::Buffer lightUniform;
    GL::Buffer drawUniform;

};

} // namespace core

#endif //CORE_MODEL_H
