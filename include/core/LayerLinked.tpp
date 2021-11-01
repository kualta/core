/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include "Layer.h"

namespace core {

template<typename T>
LayerLinked<T>::LayerLinked() {
    LinkLayer("Default");
}
template<typename T>
LayerLinked<T>::~LayerLinked() {
    UnlinkLayer("Default"); // FIXME: Change to unlink from all layers currently linked
}
template<typename T>
void LayerLinked<T>::LinkLayer(const string& name) {
    shared<Layer> layer = Layer::Get(name);
    linkedLayers.push_back(layer);
    layer->Link(*static_cast<T*>(this));
}
template<typename T>
void LayerLinked<T>::UnlinkLayer(const string& name) {
    linkedLayers.erase(std::remove_if(linkedLayers.begin(),
                                      linkedLayers.end(),
                                      [&](const shared<Layer>& l) { return l->GetName() == name; }), linkedLayers.end());
    shared<Layer> layer = Layer::Get(name);
    layer->Unlink(*static_cast<T*>(this));
}

}