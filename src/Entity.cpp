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
void Entity::Start() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->Start(); });
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
void Entity::Stop() {
    std::for_each(components.tickers.begin(), components.tickers.end(), [&](ITicker* t) { t->Stop(); });
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