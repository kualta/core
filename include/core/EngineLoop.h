#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essentials.h"
#include "Logger.h"

#include "Modules/InputModule.h"
#include <forward_list>

namespace core {

class EngineLoop {
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
     * Early update all modules
     */
    void EarlyTickModules();

    /**
     * Updates all modules
     */
    void TickModules();

    /**
     * Stops all modules
     */
    void StopModules();

    static bool  isRunning;
    InputModule* inputModule;

};

}

#endif //CORE_ENGINELOOP_H
