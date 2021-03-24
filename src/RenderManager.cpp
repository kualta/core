#include <bgfx/bgfx.h>
#include <SDL_syswm.h>
#include <LogManager.h>
#include "RenderManager.h"



namespace core {


RenderManager::RenderManager() {
    bgfx::init();
}
RenderManager::~RenderManager() {
    bgfx::shutdown();
}
bool RenderManager::CreateRenderer(Window &_window) {
    if (!InitRenderer(_window)) {
        LogManager::LogError("Cannot create renderer", INTERNAL);
        return false;
    }
    return true;
}
bgfx::PlatformData RenderManager::GetPlatformData(Window& _window) {

    SDL_SysWMinfo wmi = _window.GetSdlWmi();
    bgfx::PlatformData platformData;

    if (!SDL_GetWindowWMInfo(_window.GetSdlWindowPtr(), &wmi)) {
        LogManager::LogError("Error getting window info", INTERNAL);
    }

    #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        platformData.ndt = wmi->info.x11.display;
        platformData.nwh = (void*)(uintptr_t)wmi.info.x11.window;
    #elif BX_PLATFORM_OSX
        platformData.ndt = NULL;
        platformData.nwh = wmi->info.cocoa.window;
    #elif BX_PLATFORM_WINDOWS
        platformData.ndt = NULL;
        platformData.nwh = wmi->info.win.window;
    #elif BX_PLATFORM_STEAMLINK
        platformData.ndt = wmi->info.vivante.display;
        platformData.nwh = wmi->info.vivante.window;
    #endif // BX_PLATFORM_

    platformData.context = NULL;
    platformData.backBuffer = NULL;
    platformData.backBufferDS = NULL;

    return platformData;
}
bool RenderManager::InitRenderer(Window &_window) {

    bgfx::Init initObj;

    initObj.platformData = GetPlatformData(_window);
    initObj.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    initObj.resolution.width = _window.GetWidth();
    initObj.resolution.height = _window.GetHeight();
    initObj.resolution.reset = BGFX_RESET_VSYNC;

    if (!bgfx::init(initObj)) {
        LogManager::LogError("Error initializing renderer, aborting", INTERNAL);
        return false;
    }
    return true;
}


} // namespace