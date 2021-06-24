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