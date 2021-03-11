
#include <Utility.h>

#include "core.h"

namespace core {

/// Returns Unit ID of the created Window in core.
/// Use this ID to refer to this window from anywhere.
unsigned int core::MakeWindow(const std::string& title, Rect rect) {
    Window* _window = new Window(title, rect);

    SDL_SysWMinfo wmi;

    if (!SDL_GetWindowWMInfo(window.sdlWindow, &wmi)) {
        return false;
    }

    bgfx::PlatformData pd;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    pd.ndt = wmi.info.x11.display;
            pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
    pd.ndt = NULL;
            pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
    pd.ndt = NULL;
        pd.nwh = wmi.info.win.window;
#endif

    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData(pd);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = 640;
    bgfxInit.resolution.height = 480;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    return 0;
}


}