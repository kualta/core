#include <core/EntityPool.h>
#include <core/Entity.h>

#include <memory>


namespace core {


bool EntityPool::RegisterEntity(std::shared_ptr<Entity> entity) {
    entityPool.push_back((std::move(entity)));
}

}