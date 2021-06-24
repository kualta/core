#ifndef CORE_IWINDOWRENDERER_H
#define CORE_IWINDOWRENDERER_H

#include "Essential.h"
#include "Modules/IRenderModule.h"
#include "Object.h"

namespace core {

class IWindowRenderer : public Object {
public:

    virtual void InitWindow(Window& window) = 0;

};

}

#endif //CORE_IWINDOWRENDERER_H
