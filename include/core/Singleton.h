/*
 * This is a stand-alone header file. No Singleton.cpp is presented.
 * Check Singleton.tpp for template definitions
 */
#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


namespace core {

template <typename T> class Singleton {
public:

    /** Copuing is not allowed */
    Singleton(const Singleton<T>&) = delete;

    /** Move constructor */
    Singleton(Singleton<T>&& other) noexcept {
        singleton = static_cast<T*>(this);
    };

    /** Copuing is not allowed */
    Singleton& operator=(const Singleton<T>&) = delete;

    /** Move assignment operator */
    Singleton& operator=(Singleton<T>&& other) noexcept {
        singleton = static_cast<T*>(this);
        return *this;
    };

    Singleton() { singleton = static_cast<T*>(this); }
    ~Singleton() {

        // Do nothing, because singleton was moved
        if (singleton != static_cast<T*>(this)) { return; }

        singleton = nullptr;
    }

    static T* Get();
    static T& GetInstance();

private:

    static T* singleton;

};

} // namespace core

#include "Singleton.tpp"

#endif //CORE_SINGLETON_H
