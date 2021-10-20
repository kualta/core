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
#include <core/Object.h>
#include <core/Logger.h>


namespace core {

std::atomic<uint32_t> Object::objectCounter { 0 };

Object::Object(string name) noexcept
: name(std::move(name)), id(++objectCounter)
{
    Logger::Log(OBJECT, INFO) << "Created object " << GetInfo();
}
Object::Object(Object &&other) noexcept
: name(std::move(other.name)), id(other.id)
{
    other.id = 0;
}
Object::~Object() {
    // id == 0 means that object was moved, no need to log destruction
    if (id != 0) {
        Logger::Log(OBJECT, INFO) << "Destroyed object " << GetInfo();
    }
}
uint32_t Object::GetId() const {
    return id;
}
string Object::GetInfo() const {
    return "\"" + name + "\""  + " ID(" + std::to_string(GetId()) + ")";
}
bool Object::operator==(const Object &rhs) const {
    return id == rhs.id;
}
bool Object::operator!=(const Object &rhs) const {
    return !(id == rhs.id);
}
Object& Object::operator=(Object &&other) noexcept {
    if (this != &other) {
        Logger::Log(OBJECT, INFO) << "Object " << other.GetInfo() << " was moved into " << this->GetInfo();
        id = other.id;
        other.id = 0;
        name = std::move(other.name);
    }
    return *this;
}
const string& Object::GetName() {
    return name;
}

}