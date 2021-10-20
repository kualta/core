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
namespace core {


template <class T, class Dependent>
T* Core::GetModule() {
    auto it = moduleMap.find<T>();
    if ( it == moduleMap.end() ) {
        Logger::Log(INTERNAL, ERR_HERE) << string(typeid(T).name())
                                   << ": unsatisfied dependency of "
                                   << string(typeid(Dependent).name());

        throw std::runtime_error(string(typeid(T).name())
                                 + ": unsatisfied dependency of "
                                 + string(typeid(Dependent).name()));
    }
    return static_cast<T*>(it->second->Get());
}
template<class T>
int32_t Core::GetModuleId() {
    auto it = moduleMap.find<T>();
    if ( it == moduleMap.end() ) {
        Logger::Log(INTERNAL, ERR_HERE) << string(typeid(T).name()) << " module not found!";
        throw std::runtime_error(string(typeid(T).name()) + " module not found!");
    }
    return it->first;
}
template <class ModuleType, class Deleter, class ...Deps>
std::unique_ptr<ModuleType, Deleter> Core::Inject(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) const {
    return moduleFactory(GetModule<typename std::remove_const<Deps>::type,
            typename std::remove_const<ModuleType>::type>()...);
}

}