/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <core/Shader.h>
#include "Magnum/GL/Texture.h"
#include "Magnum/GL/Context.h"

namespace core {

shared<Shader> Shader::standard { };

Shader::Shader() {
    shader = Shaders::PhongGL { Shaders::PhongGL::Flag::DiffuseTexture
                              | Shaders::PhongGL::Flag::AmbientTexture
                              | Shaders::PhongGL::Flag::SpecularTexture
                              | Shaders::PhongGL::Flag::NormalTexture
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
void Shader::BindTextures(const Material& material) {
    shader.bindTextures(material.GetAmbientTexture()  ? material.GetAmbientTexture()->GetGLTexture()  : nullptr,
                        material.GetDiffuseTexture()  ? material.GetDiffuseTexture()->GetGLTexture()  : nullptr,
                        material.GetSpecularTexture() ? material.GetSpecularTexture()->GetGLTexture() : nullptr,
                        material.GetNormalTexture()   ? material.GetNormalTexture()->GetGLTexture()   : nullptr);
}

}