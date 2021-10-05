#ifndef CORE_ENGINECLOCK_H
#define CORE_ENGINECLOCK_H

#include "core/Essentials.h"

namespace core {

class EngineClock {
    friend class EngineLoop;
public:

    static uint64_t GetTicks();
    static float GetDeltaTime();

protected:

    static void MarkLoopStart();
    static void MarkLoopEnd();
    static void WaitNextTick();

    static uint64_t startTicks;
    static uint64_t endTicks;
    static float deltaTime;
};
}

#endif //CORE_ENGINECLOCK_H
