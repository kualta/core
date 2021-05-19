/*
 * Both CoreConfig.cpp and CoreConfig.tpp are presented.
 * Check second for template implementations.
 */
#ifndef CORE_CORECONFIG_H
#define CORE_CORECONFIG_H

#include "Essential.h"
#include "ModuleContainer.h"
#include "Core.h"

#include <functional>
#include <unordered_set>
#include <stack>

namespace core {

class CoreConfig {
public:
    /**
     * Adds module to CoreConfig
     * @details Method chaining is available
     * @tparam InstanceType - Type of module to add
     * @tparam Deleter - Deleter to use
     * @tparam Deps - Dependencies of the module
     * @return reference to this CoreConfig
     */
    template <class InstanceType, class Deleter, class ...Deps>
    CoreConfig& Add(ModuleFactory<InstanceType, Deleter, Deps...> moduleFactory);

    /**
     * Creates new Core object from this config
     * @return core::Core object
     */
    Core Build();

private:
    using initializer_fn = std::function<void(Core &)>;

    struct nodeInfo {
        enum class mark { UNMARKED, TEMP, PERM };

        mark nodeMark;

        /**
         * Used for providing type name in debug messages
         * @note Not guaranteed to be human-readable
         */
        string typeName;

        /**
         * Invokes instance factory and adds created module to the Core
         */
        initializer_fn initializer;

        bool hasIniliatizer = false;

        /**
         * List of nodes adjacent to this one
         */
        std::unordered_set<int> dependents;
    };

    /**
     * Graph of dependencies for every module
     */
    std::unordered_map<int, nodeInfo> graph;

    void VisitNode(int nodeId, std::unordered_set<int> *unmarkedNodes, std::stack<initializer_fn*> *output);
};

}

#include "CoreConfig.tpp"


#endif //CORE_CORECONFIG_H
