/**
 * This is a stand-alone header file,
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
        singleton = static_cast<T*>(this);
    }
    ~Singleton() {
        singleton = nullptr;
    }
    static T& GetInstance() {
        return (*singleton);
    }
    static T* GetInstancePtr() { return singleton; }

protected:
    /// Implementation below class template
    static T* singleton;

private:

};

// FIXME: Probabably a bad practice?
template<typename T>
T* Singleton<T>::singleton{};


}


#endif //CORE_SINGLETON_H
