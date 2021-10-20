/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
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
#include <core/Logger.h>

#include <algorithm>
#include "Pool.h"


namespace core {

template<typename T>
Pool<T>::Pool(const string& poolName) : Object(poolName) {

}
template<typename T>
void Pool<T>::Register(std::unique_ptr<T>&& objectPtr) {
    pool.push_back(std::move(objectPtr));
}
template<typename T>
void Pool<T>::Unregister(std::unique_ptr<T> &objectPtr) {
    pool.erase(std::find_if(pool.begin(), pool.end(), [&](std::shared_ptr<T>& p) {
        return *p == *objectPtr;
    }));
}
template<typename T>
void Pool<T>::Invoke(void (&f)() ) {
    std::for_each(pool.begin(), pool.end(), &f);
}


}