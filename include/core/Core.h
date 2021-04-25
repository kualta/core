#ifndef CORE_CORE_H
#define CORE_CORE_H

#include "ModuleContainer.h"
#include "Essential.h"
#include "Singleton.h"
#include "TypeMap.h"
#include "Object.h"
#include "Pool.h"

#include <memory>
#include <iterator>

namespace core {

class Core {
    friend class CoreConfig;
    using ModuleMap = TypeMap<std::unique_ptr<IModuleContainer>>;
public:
    Core(Core &&other);
    Core& operator=(Core &&other) noexcept;

    template<class T, class Dependent = std::nullptr_t>
    T* GetModule() const;

    template<class ModuleType, class Deleter, class ...Deps>
    std::unique_ptr<ModuleType, Deleter> Inject(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) const;

private:
    Core() = default;

    ModuleMap moduleMap;
};

}


#endif //CORE_CORE_H