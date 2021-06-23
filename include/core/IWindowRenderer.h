#ifndef CORE_IWINDOWRENDERER_H
#define CORE_IWINDOWRENDERER_H

#include "Essential.h"
#include "Object.h"

namespace core {

class IWindowRenderer : public Object {
public:

    bool InitWindow(Window* window);

};


}

#endif //CORE_IWINDOWRENDERER_H
