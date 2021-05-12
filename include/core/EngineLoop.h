#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essential.h"
#include "Logger.h"

#include "Modules/InputModule.h"

namespace core {

class EngineLoop {
public:
    explicit EngineLoop(InputModule* inputModule);

    /**
     * Function which contains main engine loop.
     */
    int32_t Enter();

    /**
     * Stops main engine loop after current frame.
     */
    void Stop();

protected:

    bool         isRunning { true };
    InputModule* Input;

};


}

#endif //CORE_ENGINELOOP_H
