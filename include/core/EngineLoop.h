#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essentials.h"
#include "Logger.h"

#include "Modules/InputModule.h"
#include <forward_list>

namespace core {

class EngineLoop {
    friend class EngineModule;
public:
    explicit EngineLoop(InputModule* inputModule);

    /**
     * Enters main engine loop.
     */
    int32_t Enter();

    /**
     * Stops main engine loop after current frame.
     */
    static void Stop();

protected:

    /**
     * Start all modules
     */
    void StartModules();

    /**
     * Early update all modules
     */
    void EarlyTickModules();

    /**
     * This will call Tick() function on every module added to the Core
     * @note The modules lower in the dependency hierarchy are guaranteed to be updated before * their dependants.
     */
    void TickModules();

    /**
     * Stops all modules
     */
    void StopModules();

    static bool  isRunning;
    InputModule* inputModule;

    void LateTickModules();
};

}

#endif //CORE_ENGINELOOP_H
