#ifndef CORE_POOL_H
#define CORE_POOL_H

#include "Essential.h"
#include <memory>

namespace core {

template <typename T>
class Pool {
public:

    static void Register(const std::shared_ptr<T>& objectPtr);

protected:

    static std::vector<std::shared_ptr<T>> pool;
};


}

#endif //CORE_POOL_H
