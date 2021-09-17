#ifndef CORE_POOL_H
#define CORE_POOL_H

#include "Essentials.h"
#include "Object.h"

#include <memory>

namespace core {

template <typename T>
class Pool : public Object {
public:
    explicit Pool(const string& poolName = "Unnamed pool");

    void Register(std::unique_ptr<T>&& objectPtr);
    void Unregister(std::unique_ptr<T>& objectPtr);
    void Invoke(void (&f)());

protected:

    std::vector<std::unique_ptr<T>> pool { };
};

}

#include "Pool.tpp"


#endif //CORE_POOL_H
