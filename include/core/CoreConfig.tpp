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