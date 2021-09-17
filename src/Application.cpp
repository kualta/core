#include <core/Application.h>
#include <core/Logger.h>
#include <core/Components/Camera.h>

#include <Magnum/GL/DebugOutput.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/Math/Vector2.h"

namespace core {

Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration{ }
                            .setTitle(title)
                            .setWindowFlags(Configuration::WindowFlag::Resizable)
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
    redraw();
}
void Application::resetEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth);
}
void Application::mousePressEvent(MouseEvent &event) {

}
void Application::mouseReleaseEvent(MouseEvent& event) {

}
void Application::mouseMoveEvent(MouseMoveEvent& event) {

}
void Application::viewportEvent(ViewportEvent& event) {

}


}