#ifndef INTERFACERS_ENTITY_H
#define INTERFACERS_ENTITY_H

#include <memory>
#include <utility>
#include <vector>
#include "Essential.h"
#include "Component.h"
#include "Object.h"

namespace core {

class Entity : public Object {
public:
    Entity() {}
    Entity(std::vector<std::unique_ptr<Component>> c) : components(std::move(c)) {}

    int16_t AddComponent(std::unique_ptr<Component> c);
    void Spawn();
    void Destroy();


protected:
    std::vector<std::unique_ptr<Component>> components;

private:
};

} // namespace core



#endif //INTERFACERS_ENTITY_H
