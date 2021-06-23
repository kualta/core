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
IModule* Core::GetModule(int32_t id) {
    auto it = moduleMap.find(id);
    if ( it == moduleMap.end() ) {
        Logger::Log(GENERAL, ERR) << "Module with id " << id << " not found!";
        throw std::runtime_error("Module with id " + std::to_string(id) + " not found!");
    }
    return static_cast<IModule*>(it->second->Get());
};
int32_t Core::GetModuleIdByTag(objectTag tag) {
    auto it = std::find_if(moduleTagMap.begin(),
                           moduleTagMap.end(),
                           [&](const auto& e) { return e.second == tag; });
    if ( it == moduleTagMap.end() ) {
        Logger::Log(GENERAL, ERR) << "Module with tag " << tag << " not found!";
        throw std::runtime_error("Module with tag " + std::to_string(tag) + " not found!");
    }
    return it->first;
}
template <class ModuleType, class Deleter, class ...Deps>
std::unique_ptr<ModuleType, Deleter> Core::Inject(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) const {
    return moduleFactory(GetModule<typename std::remove_const<Deps>::type,
            typename std::remove_const<ModuleType>::type>()...);
}

}