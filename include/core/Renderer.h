#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

namespace core {

class Renderer : public Singleton<Renderer>, public Object {
public:

    /**
     * Creates renderer for specific window
     */
    static bool AddRenderer(Window& window);

    /**
     *  Shuts down inner renderer
     */
    static void DestroyAll();

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

#endif //CORE_RENDERER_H
