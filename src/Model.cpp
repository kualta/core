#include <core/Model.h>
#include <core/Logger.h>
#include <core/Scene/SceneImporter.h>
#include <core/Scene/SceneData.h>
#include <core/Components/Light.h>

using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::Model(const shared<Mesh>& mesh, const shared<Shader>& shader)
: mesh(mesh), shader(shader)
{
    color = Color3::fromHsv({333.0_degf, 0.5f, 1.4f});
    Vector4 lightPositions = {0.4f, 0.0f, 0.75f, 0.0f};

//    SetLightColor(color);
    SetDiffuseColor(color);
//    shader->SetAmbientColor(Color3::fromHsv({ color.hue(), 1.0f, 0.3f }));
}
void Model::Draw(Matrix4& transformMtx, Camera& camera) {
    SetTrasfromMatrix(transformMtx);
    SetNormalMatrix(transformMtx);
    SetProjectionMatrix(camera.GetProjectionMatrix());
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
void Model::SetDiffuseColor(Color3& diffuseColor) {
    materialUniform.setData({ Shaders::PhongMaterialUniform{ }
        .setDiffuseColor(diffuseColor)
        .setAmbientColor(diffuseColor)
    });
}
void Model::SetLightColor(Light& light) {
    lightUniform.setData({ Shaders::PhongLightUniform{ }
        .setColor(light.color)
        .setRange(light.range)
        .setSpecularColor(light.specularColor)
        .setPosition({light.transform->position, 1.0f})
    });
}

}