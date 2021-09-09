#include <core/Application.h>
#include <core/Logger.h>
#include <Magnum/GL/DebugOutput.h>

#include "Magnum/GL/Renderer.h"
#include "Magnum/Math/Vector2.h"

namespace core {

Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration{ }
                            .setTitle(title)
                            .setSize(Magnum::Vector2i(rect.w, rect.h)))
{
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::enable(GL::Renderer::Feature::DebugOutput);
    GL::Renderer::enable(GL::Renderer::Feature::DebugOutputSynchronous);
    GL::DebugOutput::setDefaultCallback();
    Logger::Log(WINDOW, INFO) << "Created Application";
}
void Application::drawEvent() {
    swapBuffers();
}
void Application::resetEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth);
}
void Application::mousePressEvent(MouseEvent &event) {
    if(event.button() != MouseEvent::Button::Left) return;

    event.setAccepted();
}
void Application::mouseReleaseEvent(MouseEvent& event) {
    event.setAccepted();
    redraw();
}
void Application::mouseMoveEvent(MouseMoveEvent& event) {
    if(!(event.buttons() & MouseMoveEvent::Button::Left)) return;

    event.setAccepted();
    redraw();
}


}