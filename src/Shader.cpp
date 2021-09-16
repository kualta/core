#include <core/Shader.h>

using namespace Math::Literals;
namespace core {

Shaders::PhongGL Shader::coloredShader { NoCreate };
Shaders::PhongGL Shader::texturedShader { NoCreate };

Shader::Shader(Shaders::PhongGL* shader)
: shader(shader)
{
    texturedShader = Shaders::PhongGL { Shaders::PhongGL::Flag::DiffuseTexture };
    coloredShader = Shaders::PhongGL { };

    coloredShader
            .setAmbientColor(0x111111_rgbf)
            .setSpecularColor(0xffffff_rgbf)
            .setShininess(80.0f);
    texturedShader
            .setAmbientColor(0x111111_rgbf)
            .setSpecularColor(0x111111_rgbf)
            .setShininess(80.0f);
}
void Shader::Draw(Mesh* mesh) {
    coloredShader.draw(*mesh->GetGLMesh());
}
void Shader::SetDiffuseColor(Color3 color) {
    coloredShader.setDiffuseColor(color);
}
void Shader::SetAmbientColor(Color3 color) {
    coloredShader.setAmbientColor(Color3::fromHsv({color.hue(), 1.0f, 0.3f}));
}
void Shader::SetTransformMatrix(Matrix4& mtx) {
    coloredShader.setTransformationMatrix(mtx);
}
void Shader::SetProjectionMatrix(Matrix4& mtx) {
    coloredShader.setProjectionMatrix(mtx);
}
void Shader::SetNormalMatrix(Matrix4& mtx) {
    coloredShader.setNormalMatrix(mtx.normalMatrix());
}
void Shader::SetLightPositions(Vector4& pos) {
    coloredShader.setLightPositions({ pos });
}

}