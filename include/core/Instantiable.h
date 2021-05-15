#ifndef CORE_INSTANTIABLE_H
#define CORE_INSTANTIABLE_H

#include <vector>

namespace core {

/**
 * Helper superclass to keep track of object instances
 */
template<typename T>
class Instantiable {
public:
    Instantiable();
    ~Instantiable();

    /**
     * Vector of object instances
     */
    static std::vector<T*> instances;
};

}

#include "Instantiable.tpp"


#endif //CORE_INSTANTIABLE_H
