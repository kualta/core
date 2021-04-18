#ifndef CORE_ENTITYPOOL_H
#define CORE_ENTITYPOOL_H

#include "Essential.h"

namespace core {


class EntityPool : public Object {
public:

    bool RegisterEntity(std::shared_ptr<Entity> entity);

protected:
    static std::vector<std::shared_ptr<Entity>> entityPool;

};


}

#endif //CORE_ENTITYPOOL_H
