#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "Essentials.h"
#include "Primitive.h"

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/ImGuiIntegration/Context.hpp>
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
    void ClearBuffers();
    void Redraw();
    void SetGuiContext(ImGuiIntegration::Context* context);

protected:

    virtual void mousePressEvent(MouseEvent& event);
    virtual void mouseReleaseEvent(MouseEvent& event);
    virtual void mouseMoveEvent(MouseMoveEvent& event);
    virtual void mouseScrollEvent(MouseScrollEvent& event);
    virtual void viewportEvent(ViewportEvent& event);
    virtual void keyPressEvent(KeyEvent& event);
    virtual void textInputEvent(TextInputEvent& event);

    ImGuiIntegration::Context* gui;

private:

    virtual void drawEvent() { };
};

}

#endif //CORE_APPLICATION_H
