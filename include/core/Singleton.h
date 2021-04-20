/**
 * This is a stand-alone header file,
 * No Singleton.cpp is presented. Check Singleton.tpp for template definitions
 */
#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


namespace core {

template <typename T> class Singleton {
public:

    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

    Singleton() {
        singleton = static_cast<T*>(this);
    }
    ~Singleton() {
        singleton = nullptr;
    }
    static T& GetInstance();
    static T* Get();

protected:
    static T* singleton;

private:

};


} // namespace core


#include "Singleton.tpp"


#endif //CORE_SINGLETON_H
