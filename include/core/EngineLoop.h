#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essential.h"
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
    void Stop();

protected:

    /**
     * Updates all modules
     */
    void TickModules();

    /**
     * Stops all modules
     */
    void StopModules();

    bool         isRunning { true };
    InputModule* inputModule;

};

}

#endif //CORE_ENGINELOOP_H
