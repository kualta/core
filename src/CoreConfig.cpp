#include <core/CoreConfig.h>
#include <core/Logger.h>

namespace core {

string   ProjectInfo::name { };
uint16_t ProjectInfo::majorVersion { 0 };
uint16_t ProjectInfo::minorVersion { 0 };
uint16_t ProjectInfo::patchVersion { 0 };

CoreConfig::CoreConfig() {
    CoreInfo::SetVersion(CORE_MAJOR_VERSION, CORE_MINOR_VERSION, CORE_PATCH_VERSION);
    CoreInfo::SetName("Core Engine");
}
Core CoreConfig::Build() {
    Core core;
    std::stack<initializer_fn*> initializers;

    std::unordered_set<int> unmarkedNodes;
    for (auto &node : graph) {
        node.second.nodeMark = NodeInfo::mark::UNMARKED;
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
    NodeInfo &info = graph[nodeId];
    if (info.nodeMark == NodeInfo::mark::TEMP) {
        Logger::Log(INTERNAL, ERR_HERE) << info.typeName << " appears to be part of a cycle";
    } else if (info.nodeMark == NodeInfo::mark::UNMARKED) {
        unmarkedNodes->erase(nodeId);
        info.nodeMark = NodeInfo::mark::TEMP;
        for (int dependent : info.dependents) {
            VisitNode(dependent, unmarkedNodes, output);
        }
        info.nodeMark = NodeInfo::mark::PERM;

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

string ProjectInfo::GetVersion() {
    return std::to_string(majorVersion) + '.'
           + std::to_string(minorVersion) + '.'
           + std::to_string(patchVersion);

}
void ProjectInfo::SetVersion(uint16_t major, uint16_t minor, uint16_t patch) {
    majorVersion = major;
    minorVersion = minor;
    patchVersion = patch;
}

void ProjectInfo::SetName(const string &projName) {
    name = projName;
}

}