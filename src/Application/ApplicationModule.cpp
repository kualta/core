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
#include <core/Application/ApplicationModule.h>
#include <core/GUI/GUIContext.h>
#include <core/Input/InputModule.h>

namespace core {

ApplicationModule::ApplicationModule(InputModule*   inputModule,
                                     const string&  windowTitle,
                                     const Rect&    windowRect)
: IModule("Application", WINDOW),
inputModule(inputModule)
{
    CreateApplication(windowTitle, windowRect);
    
    Shader::standard = std::make_shared<Shader>(); // When moved to Vulkan, could be moved to Shader.cpp
}
void ApplicationModule::Start() {
    inputModule->OnViewportEvent.Subscribe([&] (ViewportEvent& event)
                                           { GL::defaultFramebuffer.setViewport({{ }, event.GetFramebufferSize()}); } );
}
void ApplicationModule::EarlyTick() {
    for (auto app : apps) {
        app->ClearBuffers();
    }
}
void ApplicationModule::LateTick() {
    SwapRedraw();
}
void ApplicationModule::CreateApplication(const string &title, Rect rect) {
    apps.push_back(new Application(title, rect));
}
void ApplicationModule::SwapRedraw() {
    for (auto app : apps) {
        app->SwapBuffers();
        app->Redraw();
    }
}
void ApplicationModule::Redraw() {
    for (auto app : apps) {
        app->Redraw();
    }
}
Vector2i ApplicationModule::GetWindowSize(uint32_t id) {
    return apps[id]->GetWindowSize();
}
Vector2 ApplicationModule::GetWindowDpiScale(uint32_t id) {
    return apps[id]->GetDpiScaling();
}
Vector2i ApplicationModule::GetWindowFrameBufferSize(uint32_t id) {
    return apps[id]->GetFrameBufferSize();
}

}