#include "Instantiable.h"
#include <algorithm>

namespace core {

template<typename T>
std::vector<T*> Instantiable<T>::instances { };

template<typename T>
Instantiable<T>::Instantiable() {
    instances.push_back(static_cast<T*>(this));
}
template<typename T>
Instantiable<T>::~Instantiable() {
    auto p = std::find(instances.begin(), instances.end(), static_cast<T*>(this));
    if ( p != instances.end() ) { instances.erase(p); }
}

}
