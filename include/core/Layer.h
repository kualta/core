#ifndef CORE_LAYER_H
#define CORE_LAYER_H

#include "Essentials.h"

namespace core {

class Layer {
public:
    static bool Exist(const string& name);
    static Layer& Get(const string& name);

    void AddEntity(Entity& entity);
    bool HasEntity(Entity& entity);
    void RemoveEntity(Entity& entity);

    const string name;

    explicit Layer(const string& name);
protected:

    static Layer& CreateNewLayer(const string& name);

    std::vector<Entity*> entities;

private:

    static std::vector<Layer> layers;

};


}

#endif //CORE_LAYER_H
