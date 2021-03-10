/*
 * This is a single-file singleton class,
 * No singleton.cpp is presented.
 */
#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


namespace core {


template <typename T> class Singleton {
private:
    /// Explicit private copy constructor. This is a forbidden operation.
    Singleton(const Singleton<T>&) = delete;
    /// Private operator= . This is a forbidden operation.
    Singleton& operator=(const Singleton<T>&) = delete;

protected:
    static T* singleton_;

public:
    Singleton() {
        singleton_ = static_cast<T*>(this);
    }
    ~Singleton() {
        singleton_ = NULL;
    }
    static T& GetInstance() {
        return (*singleton_);
    }
    static T* GetInstancePtr() { return singleton_; }
};


}


#endif //CORE_SINGLETON_H
