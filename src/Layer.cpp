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
    Logger::Log(INTERNAL, DEBUG) << "Creating new layer " << std::quoted(name);
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
        return CreateNewLayer(layerName);
    }
}
void Layer::Draw(Camera &camera) {
    for (Entity* entity : entities) {
        for (ICamDrawable* drawable : entity->components.camDrawables) {
            drawable->Draw(camera);
        }
    }
}

}