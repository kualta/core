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
#include "CoreConfig.h"

namespace core {


// Needed for the parameter pack below
template <typename ...Args>
inline void pass(Args... args) {  }

template <typename ModuleType, typename Deleter, typename ...Deps>
CoreConfig& CoreConfig::Add(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) {
    int moduleTypeId = TypeMap<NodeInfo>::typeId<typename std::remove_const<ModuleType>::type>();

    NodeInfo &newNodeInfo = graph[moduleTypeId];

    newNodeInfo.initializer = [moduleFactory](Core &core) {
        auto instance = WrapIntoModuleContainer(core.Inject(moduleFactory));
        Core::moduleMap.Put<ModuleType>(std::move(instance));
    };
    newNodeInfo.hasIniliatizer = true;
    newNodeInfo.typeName = typeid(typename std::remove_const<ModuleType>::type).name();
    pass(graph[TypeMap<NodeInfo>::typeId<typename std::remove_const<Deps>::type>()]
                 .dependents
                 .insert(moduleTypeId)...);
    return *this;
}


}