#include <core/Components/Transform.h>
#include <core/Entity.h>

namespace core {

Transform::Transform(Entity& parent, const string& name) : IComponent(parent, name) {
    parent.assertExistingComponent<Transform>();
}
void Transform::Tick() {

}

}