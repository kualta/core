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
#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "core/Essentials.h"
#include "core/Primitive.h"
#include "core/GUI/GUIContext.h"

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/ImGuiIntegration/Context.hpp>
#include <Corrade/PluginManager/Manager.h>

using namespace Magnum;
namespace core {

class Application : public Platform::Application {
    friend class ApplicationModule;
public:
    Application(const string& title = "Core Application",
                Rect           rect = { 0, 0, 1280, 720 },
                int32_t        args = 0);

    /**
     * Get DPI scaling factor of current Window
     * @return Vector2 scaling for (x, y)
     */
    Vector2 GetDpiScaling();
    
    /**
     * Get size of current Window
     * @return Vector2i size (h, w)
     */
    Vector2i GetWindowSize();
    
    /**
     * Get framebuffer size for current Window
     * @return Vector2i size (h, w)
     */
    Vector2i GetFrameBufferSize();

    /**
     * Swap framebuffers for current Window
     */
    void SwapBuffers();
    
    /**
     * Clear framebuffer
     */
    void ClearBuffers();
    
    /**
     * Redraw framebuffer
     */
    void Redraw();

private:

    void drawEvent() override { };
};

}

#endif //CORE_APPLICATION_H
