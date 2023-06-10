/*
 * This is a stand-alone header file. No Singleton.cpp is presented.
 * Check Singleton.tpp for template definitions
 */

/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
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

private:

    static T* singleton;

};

} // namespace core

#include "Singleton.tpp"

#endif //CORE_SINGLETON_H
