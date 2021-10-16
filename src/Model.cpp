#include <core/Model.h>
#include <core/Logger.h>
#include <core/Scene/SceneImporter.h>
#include <core/Scene/SceneData.h>

using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::Model(const shared<Mesh>& mesh, const shared<Shader>& shader)
: mesh(mesh), shader(shader)
{
    color = Color3::fromHsv({333.0_degf, 0.5f, 1.0f});
    Vector4 lightPositions = {1.4f, 1.0f, 0.75f, 0.0f};
}
void Model::Draw(Matrix4& transformMtx, Camera& camera) {
    shader->BindProjectionBuffer(projectionUniform);
    shader->BindTransformBuffer(transformUniform);
    shader->BindLightBuffer(lightUniform);
    shader->BindMaterialBuffer(materialUniform);
    shader->BindDrawBuffer(drawUniform);
    shader->Draw(*mesh);
}
vector<shared<Model>> Model::Load(const string& filepath) {
    SceneImporter sceneImporter;
    SceneData* sceneData = sceneImporter.ImportScene(filepath);
    return sceneImporter.ImportModels(*sceneData);
}
void Model::SetProjectionMatrix(Matrix4& mtx) {
    projectionUniform.setData({ Shaders::ProjectionUniform3D{ }.setProjectionMatrix(mtx) });
}
void Model::SetTrasfromMatrix(Matrix4& mtx) {
    transformUniform.setData({ Shaders::TransformationUniform3D{ }.setTransformationMatrix(mtx) });
}
void Model::SetNormalMatrix(Matrix4& mtx) {
    drawUniform.setData({ Shaders::PhongDrawUniform{ }.setNormalMatrix(mtx.normalMatrix()) });
}
void Model::SetDiffuseColor(Color4& diffuseColor) {
    materialUniform.setData({ Shaders::PhongMaterialUniform{ }.setDiffuseColor(diffuseColor) });
}
void Model::SetLightColor(Color3& lightColor) {
    lightUniform.setData({ Shaders::PhongLightUniform{ }.setColor(lightColor) });
}

}