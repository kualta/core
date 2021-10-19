#include <core/Shader.h>

namespace core {

shared<Shader> Shader::standard { };

Shader::Shader() {
    shader = Shaders::PhongGL { Shaders::PhongGL::Flag::DiffuseTexture
                              | Shaders::PhongGL::Flag::AmbientTexture
                              | Shaders::PhongGL::Flag::UniformBuffers };
}
void Shader::Draw(Mesh& mesh) {
    shader.draw(*mesh.GetGLMesh());
}
void Shader::BindMaterialBuffer(GL::Buffer& buffer) {
    shader.bindMaterialBuffer(buffer);
}
void Shader::BindTransformBuffer(GL::Buffer& buffer) {
    shader.bindTransformationBuffer(buffer);
}
void Shader::BindProjectionBuffer(GL::Buffer& buffer) {
    shader.bindProjectionBuffer(buffer);
}
void Shader::BindLightBuffer(GL::Buffer& buffer) {
    shader.bindLightBuffer(buffer);
}
void Shader::BindDrawBuffer(GL::Buffer& buffer) {
    shader.bindDrawBuffer(buffer);
}

}