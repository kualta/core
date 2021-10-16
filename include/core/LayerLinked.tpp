namespace core {

template<typename T>
void LayerLinked<T>::LinkLayer(const string& name) {
    Layer* layer = Layer::Get(name);
    linkedLayers.push_back(layer);
    layer->Link(*static_cast<T*>(this));
}
template<typename T>
void LayerLinked<T>::UnlinkLayer(const string& name) {
    linkedLayers.erase(std::remove_if(linkedLayers.begin(),
                                      linkedLayers.end(),
                                      [&](Layer* l) { return l->GetName() == name; }), linkedLayers.end());
    Layer* layer = Layer::Get(name);
    layer->Unlink(*static_cast<T*>(this));
}

}