#include <core/Layer.h>
#include <core/Logger.h>
#include <core/Entity.h>

#include <algorithm>
#include <iomanip>

namespace core {

std::vector<unique<Layer>> Layer::layers { };

Layer::Layer(const string &name) : Object(name) {
    if (LayerExist(name)) {
        Logger::Log(INTERNAL, ERR_HERE) << "Layer " << name << " already exists";
        throw std::runtime_error("Layer " + name + " already exists");
    }
}
Layer* Layer::CreateNewLayer(const string& name) {
    if (LayerExist(name)) {
        Logger::Log(INTERNAL, ERR_HERE) << "Layer " << name << " already exists";
        throw std::runtime_error("Layer " + name + " already exists");
    }
    unique<Layer> layer = std::make_unique<Layer>(name);
    layers.push_back(std::move(layer));
    return &(*layers.back());
}
bool Layer::LayerExist(const string& name) {
    return std::any_of(layers.begin(), layers.end(), [&](const unique<Layer>& layer) { return layer->name == name; } ) ? true : false;
}
Layer* Layer::Get(const string& layerName) {
    auto layer = std::find_if(layers.begin(), layers.end(), [&](const unique<Layer>& l) { return l->name == layerName; });
    if (layer != layers.end()) {
        return &(*(*layer));
    } else {
        Logger::Log(INTERNAL, DEBUG_HERE) << "Creating new layer " << std::quoted(layerName);
        return CreateNewLayer(layerName);
    }
}
void Layer::AddEntity(Entity& entity) {
    if (HasEntity(entity)) {
        Logger::Log(INTERNAL, WARN_HERE) << "Layer " << std::quoted(name) << " already has entity " << entity.GetInfo();
        return;
    }
    entities.push_back(&entity);
}
bool Layer::HasEntity(Entity& entity) {
    auto e = std::find(entities.begin(), entities.end(), &entity);
    return e != entities.end() ? true : false;
}
void Layer::RemoveEntity(Entity& entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&](Entity* e) { return *e == entity; }), entities.end());
}
const string& Layer::GetName() {
    return name;
}
void Layer::Draw(Camera &camera) {
    for (Entity* entity : entities) {
        for (ICamDrawable* drawable : entity->components.camDrawables) {
            drawable->Draw(camera);
        }
    }
}

}