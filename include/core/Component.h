/*
 * This is a stand-alone header file. No Component.cpp is presented.
 */
#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

#include "Essential.h"
#include "Object.h"

#include <memory>

namespace core {

/**
 *  Base class for attachments to Entity class
 */
class Component : public Object {
public:
    explicit Component(Entity* parent = nullptr, const string& name = "Unnamed")
                : Object(name + " component"), entity(parent) { };
    virtual ~Component() { };

    virtual void Update() = 0;

    /// Entity object this component is attached to
    Entity* entity { nullptr };
};

} // namespace core

#endif //CORE_COMPONENT_H
