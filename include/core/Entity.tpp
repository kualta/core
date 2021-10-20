/**
 *  core::Entity template function implementations file
 */

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
#include "Logger.h"
#include "IComponent.h"
#include "Entity.h"


namespace core {

template<template<typename> typename T, typename S, typename ...Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<IComponent, T<S>>::value, "Component S must inherit from core::IComponent");

    shared<T<S>> component = std::make_shared<T<S>>(*this, args...);
    if constexpr(std::is_base_of<ITicker, T<S>>::value)      { components.tickers.emplace_back(static_cast<ITicker*>(&(*component))); };
    if constexpr(std::is_base_of<IDrawable, T<S>>::value)    { components.drawables.emplace_back(static_cast<IDrawable*>(&(*component))); };
    components.bases.push_back(std::move(component));

    return *this;
};
template<typename T, typename... Args>
Entity& Entity::AddComponent(Args... args) {
    static_assert(std::is_base_of<IComponent, T>::value, "Component T must inherit from core::IComponent");

    auto component = std::make_shared<T>(*this, args...);
    if constexpr(std::is_base_of<ITicker, T>::value)         { components.tickers.emplace_back(static_cast<ITicker*>(&(*component))); };
    if constexpr(std::is_base_of<IDrawable, T>::value)       { components.drawables.emplace_back(static_cast<IDrawable*>(&(*component))); };
    components.bases.push_back(std::move(component));

    return *this;
}
template<typename T, typename C>
void Entity::assertRequiredComponent(C* caller) {
    static_assert(std::is_base_of<IComponent, T>::value, "Component T must inherit from core::IComponent");
    static_assert(std::is_base_of<IComponent, C>::value, "Component C must inherit from core::IComponent");
    if ( !this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " does not have component " << typeid(T).name() << ", required by " << caller->GetInfo();
        throw std::logic_error("Entity " + this->GetInfo() + " does not have component " + typeid(T).name() + ", required by " + caller->GetInfo());
    }
}
template<typename T>
void Entity::assertExistingComponent() {
    static_assert(std::is_base_of<core::IComponent, T>::value, "Component T must inherit from core::Component");
    if ( this->HasComponent<T>() ) {
        Logger::Log(OBJECT, ERR_HERE) << "Entity " << this->GetInfo() << " already has component " << typeid(T).name();
        throw std::logic_error("Entity " + this->GetInfo() + " already has component " + typeid(T).name());
    }
}

template<typename T>
T* Entity::GetComponent() {
    auto it = std::find_if(components.bases.begin(),
                           components.bases.end(),
                           [&](std::shared_ptr<IComponent> const& p)
                           { return typeid(*p).hash_code() == typeid(T).hash_code(); });
    if ( it != components.bases.end() ) {
        return dynamic_cast<T*>(it->get());
    } else {
        return nullptr;
    }
}
template<typename T>
bool Entity::HasComponent() {
    return std::any_of(components.bases.begin(), components.bases.end(),
                       [&](std::shared_ptr<IComponent> &c)
                       { return typeid(*c).hash_code() == typeid(T).hash_code(); });
}

} // namespace core