#include <core/CoreConfig.h>

namespace core {


// Needed for the parameter pack below
template <class ...Args>
inline void pass(Args... args) {  }

template <class ModuleType, class Deleter, class ...Deps>
void CoreConfig::Add(ModuleFactory<ModuleType, Deleter, Deps...> moduleFactory) {
    int moduleTypeId = TypeMap<nodeInfo>::typeId<typename std::remove_const<ModuleType>::type>();
    nodeInfo &newNodeInfo = graph[moduleTypeId];
    newNodeInfo.initializer = [moduleFactory](Core &core) {
                auto instance = WrapIntoModuleContainer(core.Inject(moduleFactory));
                core.moduleMap.put<ModuleType>(std::move(instance));
    };
    newNodeInfo.hasIniliatizer = true;
    newNodeInfo.typeName = typeid(typename std::remove_const<ModuleType>::type).name();
    pass(graph[TypeMap<nodeInfo>::typeId<typename std::remove_const<Deps>::type>()]
                 .dependents
                 .insert(moduleTypeId)...);
}

Core CoreConfig::Build() {
    Core core;
    std::stack<initializer_fn*> initializers;

    std::unordered_set<int> unmarkedNodes;
    for (auto &node : graph) {
        node.second.mark = nodeInfo::MARK::UNMARKED;
        unmarkedNodes.insert(node.first);
    }
    while ( !unmarkedNodes.empty() ) {
        int node_id = *unmarkedNodes.begin();
        VisitNode(node_id, &unmarkedNodes, &initializers);
    }
    while ( !initializers.empty() ) {
        (*initializers.top())(core);
        initializers.pop();
    }
    return std::move(core);
}

void CoreConfig::VisitNode(
        int nodeId,
        std::unordered_set<int> *unmarkedNodes,
        std::stack <CoreConfig::initializer_fn*> *output)
{
    nodeInfo &info = graph[nodeId];
    if (info.mark == nodeInfo::MARK::TEMP) {
        Logger::Log(ERR, INTERNAL) << info.typeName << " appears to be part of a cycle";
    } else if (info.mark == nodeInfo::MARK::UNMARKED) {
        unmarkedNodes->erase(nodeId);
        info.mark = nodeInfo::MARK::TEMP;
        for (int dependent : info.dependents) {
            VisitNode(dependent, unmarkedNodes, output);
        }
        info.mark = nodeInfo::MARK::PERM;

        /*
         * if hasInitializer is false, it means someone depends on this
         * node, but an module factory for this node has not been provided.
         * This will result in an injection error later.
         */
        if (info.hasIniliatizer) {
            output->push(&info.initializer);
        }
    }
}


}