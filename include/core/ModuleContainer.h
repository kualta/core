/*
 * This is a stand-alone header file, no ModuleContainer.cpp is presented
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
 * @tparam InstanceType - Moduletype to create
 * @tparam Deps - Parameters to pass to new module (dependencies)
 * @return std::unique_ptr<InstanceType>
 */
template <class InstanceType, class ...Deps>
std::unique_ptr<InstanceType> NewModule(Deps*... deps) {
    return std::make_unique<InstanceType>(deps...);
}


}

#endif //CORE_MODULECONTAINER_H
