#ifndef CORE_SCRIPTBEHAVIOUR_H
#define CORE_SCRIPTBEHAVIOUR_H

#include "Essentials.h"
#include "Entity.h"
#include "ITicker.h"

namespace core {

class ScriptBehaviour : public ITicker {
public:

    void SetEntity(Entity* e) {
        entity = e;
    }

protected:

    Entity* entity { nullptr };
};

}

#endif //CORE_SCRIPTBEHAVIOUR_H
