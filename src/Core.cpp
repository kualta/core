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
#include <core/Core.h>

#include <memory>

namespace core {

using ModuleMap = TypeMap<std::unique_ptr<IModuleContainer>>;
ModuleMap Core::moduleMap { };

Core::Core(Core &&other) {
    *this = std::move(other);
}
IModule* Core::GetModule(int32_t id) {
    auto it = moduleMap.find(id);
    if ( it == moduleMap.end() ) {
        Logger::Log(GENERAL, ERR) << "Module with id " << id << " not found!";
        throw std::runtime_error("Module with id " + std::to_string(id) + " not found!");
    }
    return static_cast<IModule*>(it->second->Get());
};
Core &Core::operator=(Core &&other) noexcept {
    return *this;
}
Core::~Core() {
    Logger::Log(INTERNAL, INFO) << "### Core destruction started ###";
}

}