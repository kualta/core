#ifndef CORE_ENTITYPOOL_H
#define CORE_ENTITYPOOL_H

#include "Essential.h"

namespace core {


class EntityPool : public Object {
public:

protected:
    static std::vector<std::shared_ptr<Entity>> entityPool;

};


}

#endif //CORE_ENTITYPOOL_H
