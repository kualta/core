#include "core.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#include <logger.h>

namespace core {


    int init() {

        if ( InitWindow() != 0 ) {
            core::Log(LOG_LEVEL::ERR, "Window initialization failed, terminating");
            //SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Fatal! Window initialization failed: %s", SDL_GetError());
            return 1;
        }

        if ( InitRender() != 0 ) {
            core::Log(LOG_LEVEL::ERR, "Render initialization failed, terminating");
        }

        if ( InitInput() != 0 ) {
            core::Log(LOG_LEVEL::ERR, "Input initialization failed, terminating");
        }

        if ( InitSound() != 0 ) {
            core::Log(LOG_LEVEL::ERR, "Sound initialization failed, terminating");
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(3000);

        SDL_DestroyWindow(window);
        SDL_Quit();

        std::cout << "- Core initialization complete -" << std::endl;
        return 0;
    }

    int InitWindow() {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            return 1;
        }

        return 0;

    }

    int InitRender() {
        // NOTE: Since bgfxInit object has to be created with platform information included we need a window for that,
        // thus we are calling bgfx::init() with no parameters on this step. We have to call another initialization
        // func after the window was created.

        bgfx::init();

        return 0;
    }

    int InitInput() {

        return 0;
    }

    int InitSound() {

        return 0;
    }

    int CreateWindow() {

        const core::Window& window;

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
