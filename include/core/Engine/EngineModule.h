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
#ifndef CORE_ENGINEMODULE_H
#define CORE_ENGINEMODULE_H

#include <core/IModule.h>
#include <core/Engine/EngineLoop.h>

#include <memory>

namespace core {

class EngineModule : public IModule {
public:
    explicit EngineModule(InputModule* input);

    void Start() override;

    static void SetTargetFrameRate(int32_t fps);
    static int32_t GetTargetFrameRate();

    int32_t Main();

    static constexpr int32_t fixedTickRate = 30;   // < Target ticks per second

protected:

    static int32_t              targetFrameRate; // < Target frames per second

    std::unique_ptr<EngineLoop> engineLoop;
    InputModule*                inputModule;

};


}


#endif //CORE_ENGINEMODULE_H
