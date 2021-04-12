#ifndef CORE_WINDOWBUILDER_H
#define CORE_WINDOWBUILDER_H

#include "Essential.h"
#include "Object.h"
#include "Singleton.h"

namespace core {

class WindowBuilder : public Object, public Singleton<WindowBuilder> {
public:

    /**
     * Creates a window and initializes a renderer for it
     * @param title - title of the window
     * @param rect - position and resolution of the window
     * @return uint32 ID of the window
     */
    static uint32_t SpawnWindow(const std::string& title, const Rect& rect);
};

} // namespace core


#endif //CORE_WINDOWBUILDER_H
