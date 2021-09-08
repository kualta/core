#include <core/Application.h>
#include <core/Logger.h>
#include <Magnum/GL/DefaultFramebuffer.h>

namespace core {


Application::Application(int args)
: Platform::Application(Arguments(args, nullptr))
{
    Logger::Log(WINDOW, INFO) << "Created Application";
}
void Application::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    swapBuffers();
}

}