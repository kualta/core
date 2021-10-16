#include <core/Components/Camera.h>
#include <core/Scene/SceneImporter.h>
#include <core/Model.h>
#include <core/Entity.h>
#include <core/Logger.h>

namespace core {

Entity::Entity(const string& name, GraphObject* parent, Layer* layer)
: core::Object(name), GraphObject(parent), layer(layer)
{
    layer->Link(*this);
}
Entity::~Entity() {
    layer->Unlink(*this);
}
bool Entity::operator!=(const Entity &rhs) const {
    return !(rhs == *this);
}
void Entity::FixedTick() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->FixedTick(); });
}
void Entity::EarlyTick() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->EarlyTick(); });
}
void Entity::Tick() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->Tick(); });
}
void Entity::LateTick() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->LateTick(); });
}
bool Entity::operator==(const Entity &rhs) const {
    return this->GetId() == rhs.GetId();
}
vector<shared<Entity>> Entity::Load(const string& filepath) {
    SceneImporter sceneImporter;
    SceneData* sceneData = sceneImporter.ImportScene(filepath);
    return sceneImporter.ImportEntities(*sceneData);
}
void Entity::SetLayer(const string& name) {
    Layer* newLayer = Layer::Get(name);
    layer->Unlink(*this);
    newLayer->Link(*this);

    layer = newLayer;
}
Layer* Entity::GetLayer() {
    return layer;
}

} // namespace core