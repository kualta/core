#ifndef CORE_POOL_H
#define CORE_POOL_H

#include "Essential.h"
#include <memory>

namespace core {

template <typename T>
class Pool : public Object {
public:
    explicit Pool(string poolName = "Unnamed pool");
    ~Pool();

    static void Register(const std::shared_ptr<T>& objectPtr);
    static void Unregister(const std::shared_ptr<T>& objectPtr);

protected:

    static std::vector<std::shared_ptr<T>> pool;
};

}

#include "Pool.tpp"


#endif //CORE_POOL_H
