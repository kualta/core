#ifndef CORE_ICOMPONENT_H
#define CORE_ICOMPONENT_H

#include "Essentials.h"
#include "ITicker.h"
#include "Object.h"

#include <memory>

namespace core {

/**
 *  Base class for attachments to Entity class
 */
class IComponent : public Object, public ITicker {
public:

    bool isActive = true;

    /// Entity object this component is attached to
    Entity* entity { nullptr };
protected:
    explicit IComponent(Entity& parent, const string& name = "Unnamed");
    virtual ~IComponent();

};

} // namespace core

#endif //CORE_ICOMPONENT_H
