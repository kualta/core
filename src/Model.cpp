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
#include <core/Model.h>
#include <core/Logger.h>
#include <core/Scene/SceneImporter.h>
#include <core/Scene/SceneData.h>
#include <core/Components/Light.h>

using namespace Magnum;
using namespace Math::Literals;
namespace core {

Model::Model(const shared<Mesh>& mesh,
             const shared<Shader>& shader,
             const shared<Material>& material)
: mesh(mesh),
  shader(shader),
  material(material)
{
    SetMaterial(material);
}
void Model::Draw() {
    shader->BindProjectionBuffer(projectionUniform);
    shader->BindTransformBuffer(transformUniform);
    shader->BindLightBuffer(lightUniform);
    shader->BindMaterialBuffer(materialUniform);
    shader->BindDrawBuffer(drawUniform);
    if (material->IsTextured()) {
        shader->BindTextures(*material);
    }
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
void Model::SetMaterial(const shared<Material>& mat) {
    material = mat;
    materialUniform.setData({ Shaders::PhongMaterialUniform{ }
        .setDiffuseColor(material->GetDiffuseColor())
        .setSpecularColor(material->GetSpecularColor())
        .setAmbientColor(material->GetAmbientColor())
        .setShininess(material->GetShininess())
        .setNormalTextureScale(material->GetNormalScale())
        .setAlphaMask(material->GetAlphaBound())
    });
}
void Model::SetLight(Light& light) {
    throw std::logic_error("Deprecated");
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
const shared<core::Mesh>& Model::GetMesh() const {
    return mesh;
}
const shared<core::Shader>& Model::GetShader() const {
    return shader;
}
const shared<core::Material>& Model::GetMaterial() const {
    return material;
}

}