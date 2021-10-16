#include <core/Components/Light.h>

namespace core {

Light::Light(Entity &parent, Color3 color, Color3 specular, float range, const string &name)
: IComponent(parent, name),
color(color),
specularColor(specular),
range(range)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
}

}