#include <core/Shader.h>

#include "Magnum/Math/Matrix4.h"
using namespace Math::Literals;
namespace core {

Shader::Shader() {

}
void Shader::Draw(Mesh* mesh) {
    shader.draw(*mesh->GetGLMesh());
}
void Shader::SetDiffuseColor(Color3 color) {
    shader.setDiffuseColor(color);
}
void Shader::SetAmbientColor(Color3 color) {
    shader.setAmbientColor(Color3::fromHsv({color.hue(), 1.0f, 0.3f}));
}
void Shader::SetTransformMatrix(Magnum::Matrix4 mtx) {
    shader.setTransformationMatrix(mtx);
}
void Shader::SetProjectionMatrix(Magnum::Matrix4 mtx) {
    shader.setProjectionMatrix(mtx);
}
void Shader::SetNormalMatrix(Magnum::Matrix4 mtx) {
    shader.setNormalMatrix(mtx.normalMatrix());
}
void Shader::SetLightPositions(Magnum::Vector4 pos) {
    shader.setLightPositions({ pos });
}

}