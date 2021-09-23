#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "Essentials.h"
#include "Primitive.h"

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Corrade/PluginManager/Manager.h>

using namespace Magnum;
namespace core {

class Application : public Platform::Application {
    friend class ApplicationModule;
public:
    Application(const string& title = "Core Window",
                Rect rect = { 0, 0, 1280, 720 },
                int32_t args = 0);

    Vector2 GetDpiScaling();
    Vector2i GetWindowSize();
    Vector2i GetFrameBufferSize();

    void SwapBuffers();
    void Redraw();


protected:

    virtual void resetEvent();
    virtual void drawEvent();
    virtual void mousePressEvent(MouseEvent& event);
    virtual void mouseReleaseEvent(MouseEvent& event);
    virtual void mouseMoveEvent(MouseMoveEvent& event);
    virtual void viewportEvent(ViewportEvent& event);
};

}

#endif //CORE_APPLICATION_H
