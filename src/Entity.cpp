#include <core/Entity.h>

namespace core {


void Entity::Spawn() {

}
void Entity::Despawn() {

}
void Entity::SetParent(Entity *newParent) {
    if ( parent ) parent->DeleteChild(this);
    if ( newParent ) newParent->AddChild(this);

    parent = newParent;
}

} // namespace core