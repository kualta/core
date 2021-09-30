#include <core/Application.h>
#include <core/Logger.h>
#include <core/Components/Camera.h>

#include <Magnum/GL/DebugOutput.h>
#include <core/GUIContext.h>
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
void Application::mousePressEvent(MouseEvent &event) {
    if (gui->HandleMousePressEvent(event)) return;
}
void Application::mouseReleaseEvent(MouseEvent& event) {
    if (gui->HandleMouseReleaseEvent(event)) return;
}
void Application::mouseMoveEvent(MouseMoveEvent& event) {
    if (gui->HandleMouseMoveEvent(event)) return;
}
void Application::mouseScrollEvent(MouseScrollEvent &event) {
    if (gui->HandleMouseScrollEvent(event)) { return; }
}
void Application::keyPressEvent(KeyEvent &event) {
    if (gui->HandleKeyPressEvent(event)) return;
}
void Application::keyReleaseEvent(KeyEvent &event) {
    if (gui->HandleKeyReleaseEvent(event)) return;
}
void Application::textInputEvent(TextInputEvent &event) {
    if (gui->HandleTextInputEvent(event)) return;
}
void Application::viewportEvent(ViewportEvent& event) {
    GL::defaultFramebuffer.setViewport({{ }, event.framebufferSize()});
    gui->Relayout(Vector2{event.windowSize()}/event.dpiScaling(), event.windowSize(), event.framebufferSize());
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
void Application::SetGuiContext(GUIContext *context) {
    gui = context;
}


}