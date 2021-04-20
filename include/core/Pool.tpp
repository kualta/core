#include <core/Logger.h>
#include <core/Window.h>

#include <algorithm>
#include "Pool.h"


namespace core {

template<typename T>
Pool<T>::Pool(string poolName) : Object(poolName) {

}
template<typename T>
void Pool<T>::Register(std::unique_ptr<T>&& objectPtr) {
    pool.push_back(std::move(objectPtr));
}
template<typename T>
void Pool<T>::Unregister(std::unique_ptr<T> &objectPtr) {
    pool.erase(std::find_if(pool.begin(), pool.end(), [&](std::shared_ptr<T>& p) {
        return *p == *objectPtr;
    }));
}


}