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
#ifndef CORE_GUIMODULE_H
#define CORE_GUIMODULE_H

#include <core/Essentials.h>
#include <core/GUI/GUIContext.h>
#include <core/IModule.h>

#include <core/Input/InputModule.h>

using namespace Magnum;
namespace core {

class GUIModule : public IModule {
public:
    explicit GUIModule(ApplicationModule* appModule, InputModule* inputModule);

protected:

    void UpdateGUI();
    void DrawGUI();

    void Start() override;
    void EarlyTick() override;
    void Tick() override;

    void SetStandardStyle();
    void SetStandardFont(float ratio);
    void SubscribeToEvents();
    void SetDefaultConfig();

    GUIContext         gui         { NoCreate };
    ApplicationModule* appModule;
    InputModule*       inputModule;

};

}

#endif //CORE_GUIMODULE_H
