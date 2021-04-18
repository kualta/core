#ifndef CORE_ENTITYPOOL_H
#define CORE_ENTITYPOOL_H

#include "Essential.h"
#include <memory>

namespace core {


class EntityPool : public Object {
public:

    static bool RegisterEntity(const std::shared_ptr<Entity>& entity);

protected:

    static void UpdateAll();


    static std::vector<std::shared_ptr<Entity>> entityPool;


};


}

#endif //CORE_ENTITYPOOL_H
