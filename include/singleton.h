#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H


namespace core {


template <typename T> class Singleton {
private:
    /// Explicit private copy constructor. This is a forbidden operation.
    Singleton(const Singleton<T>&);

    /// Private operator= . This is a forbidden operation.
    Singleton& operator=(const Singleton<T>&);

protected:
    static T* singleton_;

public:
    Singleton() {
        singleton_ = static_cast<T*>(this);
    }
    ~Singleton() {
        singleton_ = NULL;
    }
    static T& getSingleton() {
        return (*singleton_);
    }
    static T* getSingletonPtr() { return singleton_; }
};


}


#endif //CORE_SINGLETON_H
