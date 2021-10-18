#ifndef CORE_LIGHT_H
#define CORE_LIGHT_H

#include "core/Essentials.h"
#include "core/LayerLinked.h"
#include "core/IComponent.h"
#include "core/Math.h"

namespace core {

class Light : public IComponent, public LayerLinked<Light> {
public:
    explicit Light(Entity&     parent,
                   Color3       color = { 1.0f, 1.0f, 1.0f },
                   float        range =   0.0f,
                   const string& name = "Light");

    /**
     * Set color of the light
     */
    void SetColor(Color3& color);

    /**
     * Set color of the light
     */
    void SetColor(Color3&& color);

    /**
     * Set specular color of the light
     * @note By default equal to color of the light
     */
    void SetSpecularColor(Color3& color);

    /**
     * Set specular color of the light
     * @note By default equal to color of the light
     */
    void SetSpecularColor(Color3&& color);

    /**
     * Set range of the light
     */
    void SetRange(float range);

    /**
     * Get color of the light
     */
    Color3& GetColor();

    /**
     * Get specular highlight color of the light
     */
    Color3& GetSpecularColor();

    /**
     * Get range of the light
     */
    float GetRange();

protected:

    /** Light color */
    Color3 color;

    /** Specular highlight color
     * @note By default equal to the light color */
    Color3 specularColor;

    /** Attenuation range */
    float range;


    void Tick() override;

    Transform* transform { nullptr };

};

}

#endif //CORE_LIGHT_H
