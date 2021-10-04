#include <core/Application/Application.h>
#include <core/Logger.h>
#include <core/Components/Camera.h>

#include <Magnum/GL/DebugOutput.h>
#include <core/GUI/GUIContext.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/Math/Vector2.h"

namespace core {

Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration { }
                            .setTitle(title)
                            .setWindowFlags(Configuration::WindowFlag::Resizable)
                            .setSize(Magnum::Vector2i(rect.w, rect.h)))
{
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
//    GL::Renderer::enable(GL::Renderer::Feature::DebugOutput);
//    GL::Renderer::enable(GL::Renderer::Feature::DebugOutputSynchronous);

    GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add, GL::Renderer::BlendEquation::Add);
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha, GL::Renderer::BlendFunction::OneMinusSourceAlpha);

    GL::DebugOutput::setDefaultCallback();
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