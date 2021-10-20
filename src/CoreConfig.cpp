/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <core/CoreConfig.h>
#include <core/Logger.h>


namespace core {

#ifdef NDEBUG
    const bool CoreConfig::debugMode { false };
#else
    const bool CoreConfig::debugMode { true };
#endif

string   CoreConfig::AppInfo::name { "Unnamed app" };
uint16_t CoreConfig::AppInfo::majorVersion { 1 };
uint16_t CoreConfig::AppInfo::minorVersion { 0 };
uint16_t CoreConfig::AppInfo::patchVersion { 0 };

string   CoreConfig::CoreInfo::name { "Core Engine" };
uint16_t CoreConfig::CoreInfo::majorVersion { CORE_MAJOR_VERSION };
uint16_t CoreConfig::CoreInfo::minorVersion { CORE_MINOR_VERSION };
uint16_t CoreConfig::CoreInfo::patchVersion { CORE_PATCH_VERSION };

unique<Core> CoreConfig::Build() {
    unique<Core> coreContaner = std::unique_ptr<Core>(new Core);
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
        (*initializers.top())(*coreContaner);
        initializers.pop();
    }
    Logger::Log(INTERNAL, INFO) << "### Core build finished ###";
    return coreContaner;
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

void CoreConfig::AppInfo::SetVersion(uint16_t major, uint16_t minor, uint16_t patch) {
    majorVersion = major;
    minorVersion = minor;
    patchVersion = patch;
}
string CoreConfig::AppInfo::GetVersion() {
    return std::to_string(majorVersion) + '.'
           + std::to_string(minorVersion) + '.'
           + std::to_string(patchVersion);
}
void CoreConfig::AppInfo::SetName(const string &pName) {
    name = pName;
}
string CoreConfig::AppInfo::GetName() {
    return name;
}
void CoreConfig::CoreInfo::SetVersion(uint16_t major, uint16_t minor, uint16_t patch) {
    majorVersion = major;
    minorVersion = minor;
    patchVersion = patch;
}
string CoreConfig::CoreInfo::GetVersion() {
    return std::to_string(majorVersion) + '.'
           + std::to_string(minorVersion) + '.'
           + std::to_string(patchVersion);
}
void CoreConfig::CoreInfo::SetName(const string &pName) {
    name = pName;
}
string CoreConfig::CoreInfo::GetName() {
    return name;
}

}