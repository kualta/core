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
float EngineClock::GetFixedDeltaTime() {
    return 1.0f / EngineModule::fixedTickRate;
}

}