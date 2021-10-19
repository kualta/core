#include <core/Model.h>
#include <core/Logger.h>
#include <core/Scene/SceneImporter.h>
#include <core/Scene/SceneData.h>
#include <core/Components/Light.h>

using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::Model(const shared<Mesh>& mesh, const shared<Shader>& shader, const shared<Material>& material)
: mesh(mesh), shader(shader), material(material)
{
    SetMaterial(material);
}
vector<shared<Model>> Model::Load(const string& filepath) {
    SceneImporter sceneImporter;
    SceneData* sceneData = sceneImporter.ImportScene(filepath);
    return sceneImporter.ImportModels(*sceneData);
}
void Model::Draw() {
    shader->BindProjectionBuffer(projectionUniform);
    shader->BindTransformBuffer(transformUniform);
    shader->BindLightBuffer(lightUniform);
    shader->BindMaterialBuffer(materialUniform);
    shader->BindDrawBuffer(drawUniform);
    shader->Draw(*mesh);
}
void Model::SetProjectionMatrix(Matrix4& mtx) {
    projectionUniform.setData({ Shaders::ProjectionUniform3D{ }.setProjectionMatrix(mtx) });
}
void Model::SetNormalMatrix(Matrix4& mtx) {
    drawUniform.setData({ Shaders::PhongDrawUniform{ }.setNormalMatrix(mtx.normalMatrix()) });
}
void Model::SetTransformMatrix(Matrix4& mtx) {
    transformUniform.setData({ Shaders::TransformationUniform3D{ }.setTransformationMatrix(mtx) });
}
void Model::SetMaterial(Material& mat) {
    material = make_shared<Material>(mat);
    materialUniform.setData({ Shaders::PhongMaterialUniform{ }
        .setDiffuseColor(mat.GetDiffuseColor())
        .setSpecularColor(mat.GetSpecularColor())
        .setAmbientColor(mat.GetAmbientColor())
        .setShininess(mat.GetHardness())
        .setNormalTextureScale(mat.GetNormalScale())
        .setAlphaMask(mat.GetAlphaBound())
    });
}
void Model::SetMaterial(const shared<Material>& mat) {
    material = mat;
    materialUniform.setData({ Shaders::PhongMaterialUniform{ }
        .setDiffuseColor(material->GetDiffuseColor())
        .setSpecularColor(material->GetSpecularColor())
        .setAmbientColor(material->GetAmbientColor())
        .setShininess(material->GetHardness())
        .setNormalTextureScale(material->GetNormalScale())
        .setAlphaMask(material->GetAlphaBound())
    });
}
void Model::SetLight(Light& light) {
    lightUniform.setData({ Shaders::PhongLightUniform{ }
        .setColor(light.GetColor())
        .setSpecularColor(light.GetSpecularColor())
        .setRange(light.GetRange())
        .setPosition({0.0f, 0.0f, 1.0f, 0.0f}) // FIXME: handle actual data
    });
}
void Model::SetMesh(Mesh& m) {
   mesh = make_shared<Mesh>(m);
}
void Model::SetMesh(const shared<Mesh>& m) {
    mesh = m;
}
void Model::SetShader(Shader& s) {
    shader = make_shared<Shader>(std::move(s));
}
void Model::SetShader(const shared<Shader>& s) {
    shader = s;
}
void Model::SetPointLight(Light& light) {
    lightUniform.setData({ Shaders::PhongLightUniform{ }
        .setColor(light.GetColor())
        .setSpecularColor(light.GetSpecularColor())
        .setRange(light.GetRange())
        .setPosition({light.GetPosition(), 1.0f}) // FIXME relative to camera
    });
}
void Model::SetDirectionalLight(Light& light) {
    lightUniform.setData({ Shaders::PhongLightUniform{ }
        .setColor(light.GetColor())
        .setSpecularColor(light.GetSpecularColor())
        .setRange(light.GetRange())
        .setPosition({light.GetDirection(), 0.0f})
    });
}

}