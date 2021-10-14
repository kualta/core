#ifndef CORE_LAYER_H
#define CORE_LAYER_H

#include "Essentials.h"
#include "Instantiable.h"
#include "Object.h"

namespace core {

class Layer : public Object, public Instantiable<Layer> {
public:
    Layer(Layer&& other) = default;

    /** Copying is not allowed */
    Layer(const Layer& other) = delete;

    static bool LayerExist(const string& name);
    static Layer* CreateNewLayer(const string& name);
    static Layer* Get(const string& name);

    const string& GetName();
    void AddEntity(Entity& entity);
    bool HasEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

protected:

    std::vector<Entity*> entities;

private:
    explicit Layer(const string& name);

    static std::vector<Layer> layers;

};

} // namespace core

#endif //CORE_LAYER_H
