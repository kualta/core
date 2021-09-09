/*
 * Both Core.cpp and Core.tpp are presented.
 * Check second for template implementations.
 */
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
