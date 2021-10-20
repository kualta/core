/*
 * Both Core.cpp and Core.tpp are presented.
 * Check second for template implementations.
 */

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
#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "ModuleContainer.h"
#include "Essentials.h"
#include "Singleton.h"
#include "TypeMap.h"
#include "Object.h"
#include "Pool.h"

#include <memory>
#include <iterator>

namespace core {

class Core : public Singleton<Core>, public Object {
    friend class CoreConfig;
    using ModuleMap = TypeMap<std::unique_ptr<IModuleContainer>>;
public:
    Core(Core &&other);
    Core& operator=(Core &&other) noexcept;
    ~Core();

    template<class T, class Dependent = std::nullptr_t>
    static T* GetModule();

    static IModule* GetModule(int32_t id);

    template<class T>
    static int32_t GetModuleId();

    template<class ModuleType, class Deleter, class ...Deps>
    std::unique_ptr<ModuleType, Deleter> Inject(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) const;

private:
    Core() : Object("Core") { };

    static ModuleMap moduleMap;
};

}

#include "Core.tpp"


#endif //CORE_CORE_H
