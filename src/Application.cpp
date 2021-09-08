#include <core/Application.h>
#include <core/Logger.h>

#include "Magnum/Magnum.h"
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColorGL.h>

namespace core {


Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration{ }.setTitle(title).setSize(Magnum::Vector2i(rect.w, rect.h)))
{
    Logger::Log(WINDOW, INFO) << "Created Application";
}
void Application::drawEvent() {

    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);
    swapBuffers();
}

}