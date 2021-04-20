#include <core/Pool.h>
#include <core/Logger.h>

#include <algorithm>

namespace core {

template<typename T>
void Pool<T>::Register(const std::shared_ptr<T>& objectPtr) {
    pool.push_back(std::move(objectPtr));
}
template<typename T>
void Pool<T>::Unregister(const std::shared_ptr<T> &objectPtr) {
    pool.erase(std::find_if(pool.begin(), pool.end(), [&](std::shared_ptr<T>& p) {
        return *p == *objectPtr;
    }));
}
template<typename T>
Pool<T>::~Pool() {
    Logger::Log(INFO, INTERNAL) << "Destroyed " << typeid(T).name() << " pool";
}

}