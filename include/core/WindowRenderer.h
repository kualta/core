#ifndef CORE_WINDOWRENDERER_H
#define CORE_WINDOWRENDERER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

namespace core {

class WindowRenderer : public Singleton<WindowRenderer>, public Object {
public:

    /**
     * Creates renderer for specific window
     */
    static bool AddRenderer(Window& window);

    /**
     * Initializes rederer for given window
     */
    static bool InitWindow(Window& window);

    /**
     * Gathers platform data for given window
     * @return bgfx::PlatformData initialized struct
     */
    static bgfx::PlatformData GetPlatformData(const Window &window);

};

} // namespace core

#endif //CORE_WINDOWRENDERER_H
