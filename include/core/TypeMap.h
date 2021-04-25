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

// Maps types to objects of ValueType
template <class ValueType>
class type_map {
    using Container = std::unordered_map<int, ValueType>;

public:
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    iterator begin() { return container_.begin(); }
    iterator end() { return container_.end(); }
    const_iterator begin() const { return container_.begin(); }
    const_iterator end() const { return container_.end(); }
    const_iterator cbegin() const { return container_.cbegin(); }
    const_iterator cend() const { return container_.cend(); }

    template <class Key>
    iterator find() { return container_.find(type_id<Key>()); }
    template <class Key>
    const_iterator find() const { return container_.find(type_id<Key>()); }
    template <class Key>
    void put(ValueType &&value) {
        container_[type_id<Key>()] = std::forward<ValueType>(value);
    }

    template <class Key>
    static int type_id() {
        static int id = ++last_type_id_;
        return id;
    }

private:
    static std::atomic<int> last_type_id_;
    Container container_;
};

template <class T, class Deleter>
std::unique_ptr<abstract_instance_container> wrap_into_instance_container( std::unique_ptr<T, Deleter> &&ptr) {
    return std::make_unique<instance_container<T, Deleter>>(std::move(ptr));
}


}

#endif //CORE_TYPEMAP_H
