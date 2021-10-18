#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essentials.h"
#include "IDrawable.h"
#include "Material.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

#include "core/Components/Light.h"
#include <core/Components/Camera.h>
#include <core/Components/Transform.h>

namespace core {

class Model : public IDrawable {
public:
    Model(const shared<Mesh>&     mesh,
          const shared<Shader>&   shader = Shader::standard,
          const shared<Material>& material = Material::standard);

    void SetMesh(Mesh& mesh);
    void SetMesh(const shared<Mesh>& mesh);
    void SetShader(Shader& shader);
    void SetShader(const shared<Shader>& shader);
    void SetMaterial(Material& material);
    void SetMaterial(const shared<Material>& material);
    
    static vector<shared<Model>> Load(const string& filepath);

protected:
    friend class Renderer;
    friend class Layer;
    
    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;
    void SetNormalMatrix(Matrix4& mtx);
    
    void SetLight(Light& light);
    
    void Draw();

    shared<Mesh>     mesh;
    shared<Shader>   shader;
    shared<Material> material;

    GL::Buffer transformUniform;
    GL::Buffer projectionUniform;
    GL::Buffer materialUniform;
    GL::Buffer lightUniform;
    GL::Buffer drawUniform;

};

} // namespace core

#endif //CORE_MODEL_H
