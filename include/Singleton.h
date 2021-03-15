/*
 * This is a single-file singleton class,
 * No Singleton.cpp is presented.
 */
#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


namespace core {


template <typename T> class Singleton {
public:
    /// Explicit private copy constructor. This is a forbidden operation.
    Singleton(const Singleton<T>&) = delete;
    /// Private operator= . This is a forbidden operation.
    Singleton& operator=(const Singleton<T>&) = delete;
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

protected:
    static T* singleton_;

private:

};


}


#endif //CORE_SINGLETON_H
