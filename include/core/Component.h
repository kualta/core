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

    /// Entity object this component is attached to
    std::weak_ptr<Entity> entity;

protected:

private:


};

} // namespace core

#endif //CORE_COMPONENT_H
