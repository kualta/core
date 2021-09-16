#include <core/Model.h>
#include <core/Logger.h>
#include <core/SceneImporter.h>
#include <core/Components/Camera.h>


using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::~Model() {
    delete mesh;
    delete shader;
}
Model::Model() {

}
Model::Model(Mesh* mesh, Shader* shader)
: mesh(mesh), shader(shader)
{
    color = Color3::fromHsv({333.0_degf, 0.5f, 1.0f});
//    Vector4 lightPositions = {1.4f, 1.0f, 0.75f, 0.0f};
//
//    shader->SetLightPositions(lightPositions);
//    shader->SetDiffuseColor(color);
//    shader->SetAmbientColor(Color3::fromHsv({ color.hue(), 1.0f, 0.3f }));
}
void Model::Draw(Matrix4& transformMtx, Camera &camera) {
    Vector4 lightPos = { camera.cameraMatrix().transformPoint({-3.0f, 10.0f, 10.0f}), 0.0f };
    Matrix4 projMtx = camera.projectionMatrix();
    shader->SetDiffuseColor(color);
    shader->SetLightPositions(lightPos);
    shader->SetTransformMatrix(transformMtx);
    shader->SetNormalMatrix(transformMtx);
    shader->SetProjectionMatrix(projMtx);
    shader->Draw(mesh);
}
void Model::Load(const string& filepath) {
    SceneImporter sceneImporter;
    SceneData* sceneData = sceneImporter.ImportScene(filepath);
    sceneImporter.ImportObjectsFromScene(*sceneData);
}

}