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
#include <core/Layer.h>
#include <core/Logger.h>
#include <core/Entity.h>
#include <core/LayerLinked.h>
#include <core/Components/Camera.h>

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
void Layer::Draw() {

    /** For every entity attached to this layer */
    for (Entity* entity : entities) {

        /** Draw each IDrawable attached to the Entity */
        for (IDrawable* drawable : entity->components.drawables) {
            drawable->Draw();
        }

    }

}
void Layer::SetProjectionMatrix(Matrix4& mtx) {
    for (Entity* entity : entities) {
        for (IDrawable* drawable : entity->components.drawables) {
            drawable->SetProjectionMatrix(mtx);
        }
    }
}
void Layer::SetTransformMatrix(Matrix4& mtx) {
    for (Entity* entity : entities) {
        for (IDrawable* drawable : entity->components.drawables) {
            drawable->SetTransformMatrix(mtx);
        }
    }
}
void Layer::SetLight(Light& light) {
    for (Entity* entity : entities) {
        for (IDrawable* drawable : entity->components.drawables) {
            drawable->SetLight(light);
        }
    }
}

}