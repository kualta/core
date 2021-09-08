#include <core/Application.h>
#include <core/Logger.h>

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Math/Color.h>

namespace core {


Application::Application(const string& title, Rect rect, int args)
: Platform::Application(Arguments(args, nullptr),
                        Configuration{ }
                            .setTitle(title)
                            .setSize(Magnum::Vector2i(rect.w, rect.h)))
{
    Logger::Log(WINDOW, INFO) << "Created Application";
}
void Application::drawEvent() {
    swapBuffers();
}

}