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

struct ProjectInfo {
    static void SetVersion(uint16_t major, uint16_t minor, uint16_t patch);
    static string GetVersion();

    static void SetName(const string& name);
    static string GetName();

    static string name;
    static uint16_t majorVersion;
    static uint16_t minorVersion;
    static uint16_t patchVersion;
};

class CoreConfig {
    using initializer_fn = std::function<void(Core &)>;

public:
    CoreConfig();

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

    struct AppInfo : public ProjectInfo { };
    struct CoreInfo : public ProjectInfo { };

private:

    void VisitNode(int nodeId, std::unordered_set<int> *unmarkedNodes, std::stack<initializer_fn*> *output);

    struct NodeInfo {
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
    std::unordered_map<int, NodeInfo> graph;

};

}

#include "CoreConfig.tpp"


#endif //CORE_CORECONFIG_H
