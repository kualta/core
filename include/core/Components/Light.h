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
                   Color3    specular = { 1.0f, 1.0f, 1.0f },
                   float        range =   0.0f,
                   const string& name = "Light");

    /** Light color */
    Color3 color;

    /** Specular highlight color */
    Color3 specularColor;

    /** Attenuation range. */
    float range;

    Transform* transform { nullptr };

};

}

#endif //CORE_LIGHT_H
