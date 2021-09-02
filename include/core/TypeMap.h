/**
 * This is a stand-alone header file, no TypeMap.cpp is presented.
 */
#ifndef CORE_TYPEMAP_H
#define CORE_TYPEMAP_H

#include "Essential.h"

#include <atomic>
#include <memory>
#include <unordered_map>

namespace core {

/**
 * Wraps unique_ptr<T> into unique_ptr<ModuleContainer>
 * @return unique_ptr<ModuleContainer>
 */
template <typename T, typename Deleter>
std::unique_ptr<IModuleContainer> WrapIntoModuleContainer(std::unique_ptr<T, Deleter> &&ptr) {
    return std::make_unique<ModuleContainer<T, Deleter>>(std::move(ptr));
}

// FIXME: Should be moved to other namespace, TypeMap -> type_map
/**
 * Maps types to objects of ValueType
 */
template <typename ValueType>
class TypeMap {
    using Container = std::unordered_map<int, ValueType>;

public:
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    iterator begin() { return container.begin(); }
    iterator end() { return container.end(); }
    const_iterator begin() const { return container.begin(); }
    const_iterator end() const { return container.end(); }
    const_iterator cbegin() const { return container.cbegin(); }
    const_iterator cend() const { return container.cend(); }

    template <typename Key>
    iterator find() { return container.find(typeId<Key>()); }

    iterator find(int id) { return container.find(id); }

    template <typename Key>
    const_iterator find() const { return container.find(typeId<Key>()); }

    template <typename Key>
    void Put(ValueType &&value) {
        container[typeId<Key>()] = std::forward<ValueType>(value);
    }

    template <typename Key>
    static int typeId() {
        static int id = ++typeIdCounter;
        return id;
    }

private:
    static std::atomic<int> typeIdCounter;
    Container container;
};

}

#include "TypeMap.tpp"


#endif //CORE_TYPEMAP_H