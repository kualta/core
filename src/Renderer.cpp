#include <core/Renderer.h>
#include <core/Logger.h>
#include <core/Window.h>

#include <SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>


namespace core {

bool Renderer::AddRenderer(Window &window) {
    bgfx::renderFrame();
    if (!InitWindow(window)) {
        Logger::LogError("Couldn't create renderer", RENDER);
        return false;
    } else {
        Logger::LogInfo("Created renderer succesfully", RENDER);
        return true;
    }
}
void Renderer::DestroyAll() {
    bgfx::shutdown();
}
bgfx::PlatformData Renderer::GetPlatformData(const Window& _window) {

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
bool Renderer::InitWindow(Window &window) {

    bgfx::Init initObj;

    initObj.platformData = GetPlatformData(window);
    initObj.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    initObj.resolution.width = window.GetWidth();
    initObj.resolution.height = window.GetHeight();
    initObj.resolution.reset = BGFX_RESET_VSYNC;

    if (!bgfx::init(initObj)) {
        Logger::LogError("Cannot initialize renderer, aborting", RENDER);
        return false;
    }
    return true;
}


} // namespace core