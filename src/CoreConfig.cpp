#include <core/CoreConfig.h>
#include <core/Logger.h>

namespace core {


Core CoreConfig::Build() {
    Core core;
    std::stack<initializer_fn*> initializers;

    std::unordered_set<int> unmarkedNodes;
    for (auto &node : graph) {
        node.second.nodeMark = nodeInfo::mark::UNMARKED;
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
    Logger::Log(INTERNAL, INFO) << "* Core build finished * ";
    return core;
}

void CoreConfig::VisitNode(
        int nodeId,
        std::unordered_set<int> *unmarkedNodes,
        std::stack <CoreConfig::initializer_fn*> *output)
{
    nodeInfo &info = graph[nodeId];
    if (info.nodeMark == nodeInfo::mark::TEMP) {
        Logger::Log(INTERNAL, ERR_HERE) << info.typeName << " appears to be part of a cycle";
    } else if (info.nodeMark == nodeInfo::mark::UNMARKED) {
        unmarkedNodes->erase(nodeId);
        info.nodeMark = nodeInfo::mark::TEMP;
        for (int dependent : info.dependents) {
            VisitNode(dependent, unmarkedNodes, output);
        }
        info.nodeMark = nodeInfo::mark::PERM;

        /*
         * if hasInitializer is false, it means someone depends on this
         * node, but a module factory for this node has not been provided.
         * This will result in an injection error later.
         */
        if (info.hasIniliatizer) {
            output->push(&info.initializer);
        }
    }
}


}