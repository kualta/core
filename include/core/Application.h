#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include "Essential.h"
#include "Primitive.h"

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Corrade/PluginManager/Manager.h>

using namespace Magnum;
namespace core {

class Application : public Platform::Application {
public:
    Application(const string& title, Rect rect, int args = 0);

    virtual void resetEvent();
    virtual void drawEvent();

protected:

    virtual void mousePressEvent(MouseEvent& event);
    virtual void mouseReleaseEvent(MouseEvent& event);
    virtual void mouseMoveEvent(MouseMoveEvent& event);
};

}

#endif //CORE_APPLICATION_H
