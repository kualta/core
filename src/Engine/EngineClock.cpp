#include <core/Engine/EngineClock.h>
#include <core/Engine/EngineModule.h>
#include <SDL_timer.h>

#include <cmath>

namespace core {

uint64_t EngineClock::startTicks;
uint64_t EngineClock::endTicks;
float    EngineClock::deltaTime;

uint64_t EngineClock::GetTicks() {
    return SDL_GetPerformanceCounter();
}
float EngineClock::GetDeltaTime() {
    return deltaTime;
}
void EngineClock::MarkLoopStart() {
    startTicks = GetTicks();
}
void EngineClock::MarkLoopEnd() {
    endTicks = GetTicks();

    // Since GetTicks() counts performance ticks in integer space we avoid Catastrophic Cancellation, so float should
    // work fine to store deltaTime.
    deltaTime = (float)(endTicks - startTicks) / (float)SDL_GetPerformanceFrequency();
}
void EngineClock::WaitNextTick() {
    int32_t delayTime = std::floor(1000.0f / EngineModule::GetTargetFrameRate() - deltaTime * 1000.0f);
    if (delayTime < 0) return;

    SDL_Delay(delayTime);
}

}