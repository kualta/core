#ifndef CORE_LAYERLINKED_H
#define CORE_LAYERLINKED_H

#include "Essentials.h"
#include "Layer.h"

namespace core {

template<typename T> class LayerLinked {
public:
    LayerLinked();
    virtual ~LayerLinked();

    virtual void LinkLayer(const string& name);
    virtual void UnlinkLayer(const string& name);

protected:

    vector<Layer*> linkedLayers;

};

} // namespace core

#include "LayerLinked.tpp"

#endif //CORE_LAYERLINKED_H
