#include <core/Pool.h>

namespace core {

template<typename T>
void Pool<T>::Register(const std::shared_ptr<T>& objectPtr) {
    pool.push_back(std::move(objectPtr));
}

}