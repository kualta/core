#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essential.h"
#include "Logger.h"


namespace core {

class EngineLoop {
public:

    /**
     * Function which contains main engine loop.
     */
    int32_t Enter();

    /**
     * Stops main engine loop after current frame.
     */
    void Stop();

protected:

    bool isRunning { true };

};


}

#endif //CORE_ENGINELOOP_H
