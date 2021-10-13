#ifndef CORE_LAYER_H
#define CORE_LAYER_H

#include "Essentials.h"

namespace core {

class Layer {
public:
    explicit Layer(const string& name);

    /** Copying is not allowed */
    Layer(const Layer& other) = delete;

    Layer(Layer&& other) = default;

    static bool LayerExist(const string& name);
    static Layer* Get(const string& name);

    void AddEntity(Entity& entity);
    bool HasEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

protected:

    static Layer* CreateNewLayer(const string& name);

    std::vector<Entity*> entities;
    string               name;

private:

    static std::vector<Layer> layers;

};

} // namespace core

#endif //CORE_LAYER_H
