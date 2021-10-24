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
#include <core/Application/Application.h>
#include <core/Logger.h>
#include <core/Components/Camera.h>

#include <Magnum/GL/DebugOutput.h>
#include <core/GUI/GUIContext.h>
#include <core/Scene/SceneView.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/Math/Vector2.h"


namespace core {

Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration { }
                            .setTitle(title)
                            .setWindowFlags(Configuration::WindowFlag::Resizable)
                            .setSize(Vector2i(rect.w, rect.h)))
{
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
    //GL::Renderer::enable(GL::Renderer::Feature::DebugOutput);
    //GL::Renderer::enable(GL::Renderer::Feature::DebugOutputSynchronous);

    GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha, GL::Renderer::BlendFunction::OneMinusSourceAlpha);

    GL::DebugOutput::setDefaultCallback();
    
    Shader::standard = std::make_shared<Shader>(); // FIXME: Move this to Shader.cpp when GL context before application creation is implemented
    Logger::Log(WINDOW, INFO) << "Created Application";
}
Vector2i Application::GetWindowSize() {
    return windowSize();
}
Vector2 Application::GetDpiScaling() {
    return dpiScaling();
}
Vector2i Application::GetFrameBufferSize() {
    return framebufferSize();
}
void Application::SwapBuffers() {
    swapBuffers();
}
void Application::Redraw() {
    redraw();
}
void Application::ClearBuffers() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth);
}

}