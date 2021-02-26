#include "core.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#include <SDL_syswm.h>


#include <iostream>

namespace core {


    int init() {

        InitWindow();

        SDL_Window *window = SDL_CreateWindow(

                "Interfacers",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                640,
                480,
                0
        );

        InitRender();

        InitInput();
        InitSound();

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
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Fatal! Window initialization failed: %s", SDL_GetError());
            return 1;
        }

        return 0;

    }

    int InitRender() {

        SDL_SysWMinfo wmi;

        //if (!SDL_GetWindowWMInfo(_window, &wmi)) {
         //   return false;
        //}

        bgfx::PlatformData pd;

        #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
            pd.ndt = wmi.info.x11.display;
            pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
        #elif BX_PLATFORM_OSX
            pd.ndt = NULL;
            pd.nwh = wmi.info.cocoa.window;
        #elif BX_PLATFORM_WINDOWS
            pd.ndt = nullptr;
            pd.nwh = wmi.info.win.window;
        #endif

        pd.context = nullptr;
        pd.backBuffer = nullptr;
        pd.backBufferDS = nullptr;
        bgfx::setPlatformData(pd);

        bgfx::Init bgfxInit;
        bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
        bgfxInit.resolution.width = 640;
        bgfxInit.resolution.height = 480;
        bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
        bgfx::init(bgfxInit);

        return 0;
    }

    int InitInput() {

        return 0;
    }

    int InitSound() {

        return 0;
    }

    int MakeWindow() {

        return 0;
    }

}
