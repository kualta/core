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

    static vector<shared<Model>> Load(const string& filepath);

    void SetProjectionMatrix(Matrix4& mtx);
    void SetTrasfromMatrix(Matrix4& mtx);
    void SetNormalMatrix(Matrix4& mtx);
    void SetDiffuseColor(Color3& color);
    void SetAmbientColor(Color4& color);
    void SetLightColor(Color3& color, Vector4& lightPos);

protected:
    friend class Renderer;

    void Draw(Matrix4& transformMtx, Camera& camera);

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
