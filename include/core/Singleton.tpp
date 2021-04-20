/**
 *  core::Singleton template function implementations file
 */

#include "Singleton.h"

namespace core {

template<typename T>
T* Singleton<T>::singleton {  };

template<typename T>
T *Singleton<T>::Get() {
    return singleton;
}
template<typename T>
T &Singleton<T>::GetInstance() {
    return (*singleton);
}

} // namespace core