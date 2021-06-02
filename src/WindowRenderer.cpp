#include <core/WindowRenderer.h>
#include <core/Logger.h>
#include <core/Window.h>

#include <SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

namespace core {

bool WindowRenderer::AddRenderer(Window &window) {
    if (!InitWindow(window)) {
        Logger::Log(RENDER, ERR_HERE) << "Couldn't create renderer";
        return false;
    } else {
        Logger::Log(RENDER, INFO) << "Created renderer succesfully";
        return true;
    }
}
bgfx::PlatformData WindowRenderer::GetPlatformData(const Window& _window) {

    SDL_SysWMinfo *wmi = _window.GetSdlWmi();
    bgfx::PlatformData platformData;

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
bool WindowRenderer::InitWindow(Window &window) {

    bgfx::Init initObj;

    initObj.platformData = GetPlatformData(window);
    initObj.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    initObj.resolution.width = window.GetWidth();
    initObj.resolution.height = window.GetHeight();
    initObj.resolution.reset = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X4;

    bool success = bgfx::init(initObj);

    if (success) {
        Logger::Log(RENDER, INFO) << "Initialized renderer for window \"" << window.GetTitle() << "\" ";
        return true;
    } else {
        Logger::Log(RENDER, ERR_HERE) << "Cannot initialize renderer, aborting";
        return false;
    }
}


} // namespace core