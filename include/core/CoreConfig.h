/*
 * Both CoreConfig.cpp and CoreConfig.tpp are presented.
 * Check second for template implementations.
 */

/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#ifndef CORE_CORECONFIG_H
#define CORE_CORECONFIG_H

#include "Essentials.h"
#include "ModuleContainer.h"
#include "Core.h"

#include <functional>
#include <unordered_set>
#include <stack>

namespace core {

class CoreConfig {
    using initializer_fn = std::function<void(Core &)>;

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
    unique<Core> Build();

    struct AppInfo {
        static void SetVersion(uint16_t major, uint16_t minor, uint16_t patch);
        static string GetVersion();

        static void SetName(const string& name);
        static string GetName();

        static string name;
        static uint16_t majorVersion;
        static uint16_t minorVersion;
        static uint16_t patchVersion;
    };

    struct CoreInfo {
        static void SetVersion(uint16_t major, uint16_t minor, uint16_t patch);
        static string GetVersion();

        static void SetName(const string& name);
        static string GetName();

        static string name;
        static uint16_t majorVersion;
        static uint16_t minorVersion;
        static uint16_t patchVersion;
    };

    const static bool debugMode;

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
