#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "core/Essentials.h"
#include "core/Logger.h"
#include "core/Engine/EngineClock.h"
#include "core/Input/InputModule.h"

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
     * Loop that is kept in charge of FixedTick()
     */
    void FixedTickLoop();

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
     * Updates modules in fixed time periods
     * @note See EngineClock::fixedDeltaTime
     */
    void FixedTickModules();

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
