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
    template <class InstanceType, class Deleter, class ...Deps>
    void Add(ModuleFactory<InstanceType, Deleter, Deps...> moduleFactory);

    Core Build();

private:
    using initializer_fn = std::function<void(Core &)>;

    struct nodeInfo {
        enum class MARK { UNMARKED, TEMP, PERM };

        MARK mark;

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
     * Graph of all dependencies for every module
     */
    std::unordered_map<int, nodeInfo> graph;

    void VisitNode(int nodeId, std::unordered_set<int> *unmarkedNodes, std::stack<initializer_fn*> *output);
};

}

#include "CoreConfig.tpp"


#endif //CORE_CORECONFIG_H
