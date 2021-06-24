#ifndef CORE_BGFXWINDOWRENDERER_H
#define CORE_BGFXWINDOWRENDERER_H

#include "Essential.h"
#include "IWindowRenderer.h"

namespace core {

class BgfxWindowRenderer : public IWindowRenderer {
public:

    /**
     * Creates renderer for specific window
     */
    bool AddRenderer(Window& window);

    /**
     * Initializes rederer for given window
     */
    bool InitWindow(Window& window);

    /**
     * Gathers platform data for given window
     * @return bgfx::PlatformData initialized struct
     */
    static bgfx::PlatformData GetPlatformData(const Window &window);

};

} // namespace core

#endif //CORE_BGFXWINDOWRENDERER_H
