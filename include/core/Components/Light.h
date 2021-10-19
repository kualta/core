#ifndef CORE_LIGHT_H
#define CORE_LIGHT_H

#include "core/Essentials.h"
#include "core/LayerLinked.h"
#include "core/IComponent.h"
#include "core/Math.h"

namespace core {

enum LightType {
    Point,
    Directional,
    Spot,           // TODO: not yet implemented
    Area            // TODO: not yet implemented
};

class Light : public IComponent, public LayerLinked<Light> {
public:
    explicit Light(Entity& parent,
                   LightType lightType  = LightType::Spot,
                   Color3 color         = { 1.0f, 1.0f, 1.0f },
                   float range          = 0.0f,
                   const string& name   = "Light");

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
     * Make this light behave like light of the type
     */
    void SetLightType(LightType type);

    /**
     * Set range of the light
     */
    void SetRange(float range);
    
    /**
     * Get Type of the light
     * @details Avaiable types: Spot, Point, Directional, Area
     */
    LightType GetLightType() const;
    
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
    
    /**
     * Get position of the light
     */
    Vector3& GetPosition();
    
    /**
     * Get direction of the light
     */
    Vector3 GetDirection();
    
    
protected:
    
    void Tick() override;
    
    
    /** Light color */
    Color3 color;

    /** Specular highlight color
     * @note By default equal to the light color */
    Color3 specularColor;

    /** Attenuation range */
    float range;
    
    /* Type of light */
    LightType lightType;
    
    
    Transform* transform { nullptr };
    
};

}

#endif //CORE_LIGHT_H
