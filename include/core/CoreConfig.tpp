namespace core {


// Needed for the parameter pack below
template <class ...Args>
inline void pass(Args... args) {  }

template <class ModuleType, class Deleter, class ...Deps>
CoreConfig& CoreConfig::Add(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) {
    int moduleTypeId = TypeMap<nodeInfo>::typeId<typename std::remove_const<ModuleType>::type>();
    nodeInfo &newNodeInfo = graph[moduleTypeId];
    newNodeInfo.initializer = [moduleFactory](Core &core) {
        auto instance = WrapIntoModuleContainer(core.Inject(moduleFactory));
        Core::moduleMap.Put<ModuleType>(std::move(instance));
    };
    newNodeInfo.hasIniliatizer = true;
    newNodeInfo.typeName = typeid(typename std::remove_const<ModuleType>::type).name();
    pass(graph[TypeMap<nodeInfo>::typeId<typename std::remove_const<Deps>::type>()]
                 .dependents
                 .insert(moduleTypeId)...);
    return *this;
}


}