namespace core {


template <class T, class Dependent>
T* Core::GetModule() {
    auto it = moduleMap.find<T>();
    if ( it == moduleMap.end() ) {
        Logger::Log(ERR, INTERNAL) << string(typeid(T).name())
                                   << ": unsatisfied dependency of "
                                   << string(typeid(Dependent).name());

        throw std::runtime_error(string(typeid(T).name())
                                 + ": unsatisfied dependency of "
                                 + string(typeid(Dependent).name()));
    }
    return static_cast<T*>(it->second->Get());
}

template <class ModuleType, class Deleter, class ...Deps>
std::unique_ptr<ModuleType, Deleter> Core::Inject(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) const {
    return moduleFactory(GetModule<typename std::remove_const<Deps>::type,
            typename std::remove_const<ModuleType>::type>()...);
}

}