#include <core/Model.h>
#include <core/Logger.h>


using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::~Model() {
    delete mesh;
    delete shader;
}
Model::Model(Mesh* _mesh, Shader* _shader)
: mesh(_mesh), shader(_shader)
{
    color = Color3::fromHsv({333.0_degf, 0.5f, 1.0f});
    shader->SetLightPositions({1.4f, 1.0f, 0.75f, 0.0f});
    shader->SetDiffuseColor(color);
    shader->SetAmbientColor(Color3::fromHsv({ color.hue(), 1.0f, 0.3f }));
}
void Model::Draw() {
    transformMtx = Magnum::Matrix4::rotationX(30.0_degf) * Magnum::Matrix4::rotationY(40.0_degf);
    projectionMtx = Magnum::Matrix4::perspectiveProjection(
                    35.0_degf, Magnum::Vector2{1280, 720}.aspectRatio(), 0.01f, 100.0f) *
                    Magnum::Matrix4::translation(Magnum::Vector3::zAxis(-10.0f));

    shader->SetTransformMatrix(transformMtx);
    shader->SetNormalMatrix(transformMtx);
    shader->SetProjectionMatrix(projectionMtx);

    shader->Draw(mesh);
}

}