#include <core/EntityPool.h>
#include <core/Entity.h>

#include <memory>


namespace core {

std::vector<std::shared_ptr<Entity>> EntityPool::entityPool { };

bool EntityPool::RegisterEntity(const std::shared_ptr<Entity>& entity) {
    entityPool.push_back(entity);
    return true;
}
void EntityPool::UpdateAll() {
    std::for_each(entityPool.begin(), entityPool.end(), [&](std::shared_ptr<Entity> &ent) {
        ent->Update();
    });
}
void EntityPool::DrawAll() {
    std::for_each(entityPool.begin(), entityPool.end(), [&](std::shared_ptr<Entity> &ent) {
        ent->Draw();
    });

}


} // namespace core