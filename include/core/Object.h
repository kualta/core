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
#ifndef CORE_OBJECTID_H
#define CORE_OBJECTID_H

#include "Essentials.h"

#include <utility>
#include <atomic>

namespace core {

/**
 *  Base class of every countable class
 */
class Object {
public:
    /** Move constructor */
    Object(Object&& other) noexcept;

    /** Copying is not allowed */
    Object(const Object&) = delete;

    /**
     * @return std::string Name of the object
     */
    const string& GetName();

    /**
     * @return uint32_t ID of the object
     */
    uint32_t GetId() const;

    /**
     * @return string with name and ID of the object
     * @details format: "name" ID(123)
     */
    string GetInfo() const;

    /** Copying is not allowed */
    Object& operator=(const Object&) = delete;

    /** Move assignment */
    Object& operator=(Object&& other) noexcept;

    bool operator==(const Object &rhs) const;
    bool operator!=(const Object &rhs) const;

protected:

    explicit Object(string name = "") noexcept;
    virtual ~Object();

    string name;

private:

    static std::atomic<uint32_t> objectCounter;

    uint32_t id;

};

} // namespace core

#endif //CORE_OBJECTID_H
