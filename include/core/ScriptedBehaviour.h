#ifndef CORE_SCRIPTEDBEHAVIOUR_H
#define CORE_SCRIPTEDBEHAVIOUR_H

#include "Essentials.h"
#include "Entity.h"
#include "ITicker.h"

namespace core {

class ScriptedBehaviour : public ITicker {
public:
    virtual ~ScriptedBehaviour() = default;

    void SetEntity(Entity* e) {
        entity = e;
    }

protected:

    Entity* entity { nullptr };
};

}

#endif //CORE_SCRIPTEDBEHAVIOUR_H
