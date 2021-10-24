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
#include <core/Material.h>

namespace core {

const shared<Material> Material::standard = make_shared<Material>(0xe1f2fbff_rgbaf);

Material::Material(const shared<Texture>& diffuseTexture,
                   const shared<Texture>& ambientTexture,
                   const shared<Texture>& specularTexture,
                   const shared<Texture>& normalTexture,
                   Color4 diffuseColor,
                   Color4 ambientColor,
                   Color4 specularColor,
                   float normalScale,
                   float shininess,
                   float alphaBound)
: ambientColor(ambientColor),
  diffuseColor(diffuseColor),
  specularColor(specularColor),
  normalScale(normalScale),
  shininess(shininess),
  alphaBound(alphaBound),
  diffuseTexture(diffuseTexture),
  ambientTexture(ambientTexture),
  specularTexture(specularTexture),
  normalTexture(normalTexture)
{

}
Material::Material(Color4 diffuseColor,
                   Color4 ambientColor,
                   Color4 specularColor,
                   float normalScale,
                   float shininess,
                   float alphaBound)
: ambientColor(ambientColor),
  diffuseColor(diffuseColor),
  specularColor(specularColor),
  normalScale(normalScale),
  shininess(shininess),
  alphaBound(alphaBound),
  diffuseTexture(nullptr),
  ambientTexture(nullptr),
  specularTexture(nullptr),
  normalTexture(nullptr)
{

}
const Color4& Material::GetAmbientColor() const {
    return ambientColor;
}
void Material::SetAmbientColor(const Color4& color) {
    ambientColor = color;
}
const Color4& Material::GetDiffuseColor() const {
    return diffuseColor;
}
void Material::SetDiffuseColor(const Color4& color) {
    diffuseColor = color;
}
const Color4& Material::GetSpecularColor() const {
    return specularColor;
}
void Material::SetSpecularColor(const Color4& color) {
    specularColor = color;
}
float Material::GetNormalScale() const {
    return normalScale;
}
void Material::SetNormalScale(float scale) {
    normalScale = scale;
}
float Material::GetShininess() const {
    return shininess;
}
void Material::SetShininess(float value) {
    shininess = value;
}
float Material::GetAlphaBound() const {
    return alphaBound;
}
void Material::SetAlphaBound(float value) {
    alphaBound = value;
}
const shared<Texture>& Material::GetDiffuseTexture() const {
    return diffuseTexture;
}
const shared<Texture>& Material::GetAmbientTexture() const {
    return ambientTexture;
}
void Material::SetAmbientTexture(const shared<Texture>& ambient) {
    Material::ambientTexture = ambient;
}
const shared<Texture>& Material::GetSpecularTexture() const {
    return specularTexture;
}
void Material::SetSpecularTexture(const shared<Texture>& specular) {
    Material::specularTexture = specular;
}
const shared<Texture>& Material::GetNormalTexture() const {
    return normalTexture;
}
void Material::SetNormalTexture(const shared<Texture>& normal) {
    Material::normalTexture = normal;
}
bool Material::IsTextured() const {
    return diffuseTexture || normalTexture || specularTexture || ambientTexture;
}
void Material::SetDiffuseTexture(const shared<Texture>& texture) {
    diffuseTexture = texture;
}

}