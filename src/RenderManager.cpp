#include <bgfx/bgfx.h>
#include <SDL_syswm.h>
#include <LogManager.h>
#include "RenderManager.h"



namespace core {


RenderManager::RenderManager() {
    bgfx::init();
}
RenderManager::~RenderManager() {
}
bool RenderManager::CreateRenderer(Window &_window) {

    bgfx::PlatformData pd;
    if (!SDL_GetWindowWMInfo(_window.GetSdlWindowPtr(), &_window.wmi)) {
        LogManager::LogError("Error getting window info, aborting", RENDER);
        return false;
    }
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
    pd.ndt = NULL;
    pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
    pd.ndt = NULL;
    pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_STEAMLINK
    pd.ndt = wmi.info.vivante.display;
    pd.nwh = wmi.info.vivante.window;
#endif // BX_PLATFORM_
    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;

    bgfx::Init bgfxInit;
    bgfxInit.platformData = pd;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = WNDW_WIDTH;
    bgfxInit.resolution.height = WNDW_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);
}
bgdx::PlatformData RenderManager::GetPlatformData(Window &window) {

}

}