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
#include <core/Engine/EngineLoop.h>
#include <core/Engine/EngineModule.h>

#include <SDL.h>
#include <SDL_syswm.h>
#include <chrono>
#include <thread>

namespace core {

bool EngineLoop::isRunning { true };

EngineLoop::EngineLoop(InputModule* inputModule) : inputModule(inputModule) {

}
int32_t EngineLoop::Enter() {

    std::thread fixedLoopThread(&EngineLoop::FixedTickLoop, this);

    while ( isRunning ) {

        EngineClock::MarkLoopStart();

        /** Called before the frame is drawn */
        this->EarlyTickModules();

        /** Update modules & draw frame */
        this->TickModules();

        /** Called after the frame has been drawn */
        this->LateTickModules();

        EngineClock::MarkLoopEnd();

        /** Pauses engine execution to match EngineModule::targetFrameRate */
        EngineClock::WaitNextTick();

    } // main loop

    fixedLoopThread.join();

    return 0;
}
void EngineLoop::StartModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Start();
    });
}
void EngineLoop::StopModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Stop();
    });
}
void EngineLoop::EarlyTickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->EarlyTick();
    });
}
void EngineLoop::TickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->Tick();
    });
}
void EngineLoop::LateTickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->LateTick();
    });
}
void EngineLoop::FixedTickModules() {
    std::for_each(IModule::instances.begin(), IModule::instances.end(), [&](IModule* module) {
        module->FixedTick();
    });
}
void EngineLoop::Stop() {
    Logger::Log(INTERNAL, INFO) << "Main loop exit requested";
    isRunning = false;
}
void EngineLoop::FixedTickLoop() {
    Logger::Log(INTERNAL, INFO) << "Fixed Tick loop started";

    using delta = std::chrono::duration<std::int64_t, std::ratio<1, EngineModule::fixedTickRate>>;
    auto nextTick = std::chrono::steady_clock::now() + delta { 1 };

    while ( isRunning ) {

        /** Call FixedTick() on modules */
        this->FixedTickModules();

        std::this_thread::sleep_until(nextTick);
        nextTick += delta { 1 };
    }
    Logger::Log(INTERNAL, INFO) << "Fixed Tick loop stopped";
}

}