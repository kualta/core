#ifndef CORE_MATERIAL_H
#define CORE_MATERIAL_H

#include "Essentials.h"
#include "Math.h"

namespace core {

class Material {
public:
    explicit Material(Color4 color       = 0xffffffff_rgbaf,
                      float  normalScale = 1.0f,
                      float  shininess   = 40.0f,
                      float  alphaBound  = 0.5f);

    explicit Material(Color4 ambient     = 0xffffffff_rgbaf,
                      Color4 diffuse     = 0xffffffff_rgbaf,
                      Color4 specular    = 0xffffff00_rgbaf,
                      float  normalScale = 1.0f,
                      float  shininess   = 40.0f,
                      float  alphaBound  = 0.5f);

    const Color4& GetAmbientColor() const;
    const Color4& GetDiffuseColor() const;
    const Color4& GetSpecularColor() const;
    float GetNormalScale() const;
    float GetHardness() const;
    float GetAlphaBound() const;

    void SetAmbientColor(const Color4& ambientColor);
    void SetDiffuseColor(const Color4& diffuseColor);
    void SetSpecularColor(const Color4& specularColor);
    void SetNormalScale(float normalScale);
    void SetHardness(float hardness);
    void SetAlphaBound(float alphaBound);
    
    static const shared<Material> standard;

protected:

    /** Ambient color */
    Color4 ambientColor;

protected:

    /** Diffuse color */
    Color4 diffuseColor;

    /** Specular color */
    Color4 specularColor;

    /** Normal texture strength multiplier */
    float normalScale;

    /** Shininess
     * @details The larger value, the smaller specular highlight */
    float shininess;

    /** Alpha mask bound color
     * @details Fragments with alpha values smaller than the mask value will be discarded */
    float alphaBound;

};

}

#endif //CORE_MATERIAL_H
