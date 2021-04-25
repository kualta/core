#ifndef CORE_ROOT_H
#define CORE_ROOT_H

#include "ModuleContainer.h"
#include "Essential.h"
#include "Singleton.h"
#include "TypeMap.h"
#include "Object.h"
#include "Pool.h"

#include <memory>
#include <iterator>

namespace core {

template <class InstanceType, class Deleter, class ...Deps>
using instance_factory_function = std::unique_ptr<InstanceType, Deleter>(*)(Deps*...);


class injector {
    friend class di_config;
public:
    injector(injector &&other) { *this = std::move(other); }
    injector& operator=(injector &&other) { instance_map_ = std::move(other.instance_map_); }

    template <class T, class Dependent = std::nullptr_t>
    T* get_instance() const;

    template <class InstanceType, class Deleter, class ...Deps>
    std::unique_ptr<InstanceType, Deleter> inject(
            instance_factory_function<InstanceType, Deleter, Deps...> instance_factory) const;

private:
    injector() = default;
    using instance_map = type_map<std::unique_ptr<abstract_instance_container>>;
    instance_map instance_map_;
};



class Root : public Singleton<Root>, public Object {
public:

    /**
     *  Initializes the engine
     */
    Root();

    /**
     *  Uninitializes the engine
     */
    ~Root();

    std::unique_ptr<Pool<Window>> windowPool;
};

}


#endif //CORE_ROOT_H
