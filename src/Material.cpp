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

const shared<Material> Material::standard = make_shared<Material>(0xe1f2fbff_rgbaf, 1.0f, 100.0f, 0.5f);

Material::Material(const shared<GL::Texture2D>& texture,
                   float normalScale,
                   float shininess,
                   float alphaBound)
: texture(texture),
  ambientColor(0xffffffff_rgbaf),
  diffuseColor(0xffffffff_rgbaf),
  specularColor(0xffffffff_rgbaf),
  normalScale(normalScale),
  shininess(shininess),
  alphaBound(alphaBound)
{

}
Material::Material(Color4 color,
                   float normalScale,
                   float shininess,
                   float alphaBound)
: texture(nullptr),
  ambientColor(color),
  diffuseColor(color),
  specularColor(color),
  normalScale(normalScale),
  shininess(shininess),
  alphaBound(alphaBound)
{

}
Material::Material(Color4 ambient,
                   Color4 diffuse,
                   Color4 specular,
                   float normalScale,
                   float shininess,
                   float alphaBound)
: texture(nullptr),
  ambientColor(ambient),
  diffuseColor(diffuse),
  specularColor(specular),
  normalScale(normalScale),
  shininess(shininess),
  alphaBound(alphaBound)
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
float Material::GetHardness() const {
    return shininess;
}
void Material::SetHardness(float value) {
    shininess = value;
}
float Material::GetAlphaBound() const {
    return alphaBound;
}
void Material::SetAlphaBound(float value) {
    alphaBound = value;
}
const GL::Texture2D* Material::GetTexture() const {
    return texture.get();
}
bool Material::HasTexture() const {
    return texture ? true : false;
}

}