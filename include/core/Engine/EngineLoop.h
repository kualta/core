/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
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
