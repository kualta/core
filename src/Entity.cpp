#include <core/Entity.h>

namespace core {


int16_t Entity::AddComponent(std::unique_ptr<Component> c) {
    components.push_back(c);
    return components.size() - 1;
}


} // namespace core