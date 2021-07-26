#ifndef CORE_BGFXWINDOWRENDERER_H
#define CORE_BGFXWINDOWRENDERER_H

#include "core/Essential.h"
#include "core/IWindowRenderer.h"

namespace core {

class BgfxWindowRenderer : public IWindowRenderer {
public:

    /**
     * Creates renderer for specific window
     */
    void AddRenderer(Window& window);

    /**
     * Initializes rederer for given window
     */
    void InitWindow(Window& window);

    /**
     * Gathers platform data for given window
     * @return bgfx::PlatformData initialized struct
     */
    static bgfx::PlatformData GetPlatformData(const Window &window);

};

} // namespace core

#endif //CORE_BGFXWINDOWRENDERER_H
