#include <core/Material.h>

namespace core {

const shared<Material> Material::standard = make_shared<Material>(0xe1f2fbff_rgbaf, 1.0f, 100.0f, 0.5f);

Material::Material(Color4 color,
                   float normalScale,
                   float hardness,
                   float alphaBound)
: ambientColor(color),
  diffuseColor(color),
  specularColor(color),
  normalScale(normalScale),
  hardness(hardness),
  alphaBound(alphaBound)
{

}
Material::Material(Color4 ambient,
                   Color4 diffuse,
                   Color4 specular,
                   float normalScale,
                   float hardness,
                   float alphaBound)
: ambientColor(ambient),
  diffuseColor(diffuse),
  specularColor(specular),
  normalScale(normalScale),
  hardness(hardness),
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
    return hardness;
}
void Material::SetHardness(float value) {
    hardness = value;
}
float Material::GetAlphaBound() const {
    return alphaBound;
}
void Material::SetAlphaBound(float value) {
    alphaBound = value;
}

}