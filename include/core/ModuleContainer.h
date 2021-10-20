/*
 * This is a stand-alone header file. No ModuleContainer.cpp is presented.
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
#ifndef CORE_MODULECONTAINER_H
#define CORE_MODULECONTAINER_H

#include "Essentials.h"

#include <memory>

namespace core {

template<class InstanceType, class Deleter, class ...Deps>
using ModuleFactory = std::unique_ptr<InstanceType, Deleter>(*)(Deps*...);

/**
 * Stores raw ptr to module of an arbitrary class.
 */
class IModuleContainer {
public:
    virtual ~IModuleContainer() = default;

    void* Get() { return rawPtr; }

    IModuleContainer(IModuleContainer &&other) noexcept {
        *this = std::move(other);
    }

    IModuleContainer& operator=(IModuleContainer &&other) noexcept {
        rawPtr = other.rawPtr;
        other.rawPtr = nullptr;
        return *this;
    }

protected:
    explicit IModuleContainer(void *rawPtr) : rawPtr(rawPtr) { }

private:
    void* rawPtr { };
};


/**
 * Stores ptr to module of an arbitrary class and manages its lifetime
 */
template <class T, class Deleter>
class ModuleContainer : public IModuleContainer {
public:
    ~ModuleContainer() override = default;

    explicit ModuleContainer(std::unique_ptr<T, Deleter> &&p) :
            IModuleContainer(p.get()),
            ptr(std::move(p)) {}

    ModuleContainer(ModuleContainer &&other) {
        *this = std::move(other);
    }

    ModuleContainer& operator=(ModuleContainer &&other) noexcept {
        ptr = std::move(other);
        IModuleContainer::operator=(std::move(other));
        return *this;
    }

private:
    std::unique_ptr<T, Deleter> ptr;
};

/**
 * Helper factory function that creates instance of module
 * and passes all parameters to its constructor.
 * @tparam T - Moduletype to create
 * @tparam Deps - Parameters to pass to new module (dependencies)
 * @return std::unique_ptr<InstanceType>
 */
template <class T, class ...Deps>
std::unique_ptr<T> NewModule(Deps*... deps) {
    static_assert(std::is_base_of<core::IModule, T>::value, "Module T must inherit from core::IModule");
    return std::make_unique<T>(deps...);
}


}

#endif //CORE_MODULECONTAINER_H
