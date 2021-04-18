#include <core/EntityPool.h>
#include <core/Entity.h>

#include <memory>


namespace core {


bool EntityPool::RegisterEntity(const std::shared_ptr<Entity>& entity) {
    entityPool.push_back(entity);
    return true;
}
void EntityPool::UpdateAll() {
    std::for_each(entityPool.begin(), entityPool.end(), [&](std::shared_ptr<Entity> &ent) {
        ent->Update();
    });
}


} // namespace core