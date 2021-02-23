#include "core.h"

#include "bgfx/bgfx.h"
#include "SDL.h"


#include <iostream>

namespace core {


    int init() {

        InitWindow();

        InitRender();
        InitInput();
        InitSound();

        SDL_Window *window = SDL_CreateWindow(
                "Interfacers",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                640,
                480,
                0
        );

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

    }

    int CreateWindow() {

    }

    int InitRender() {
        bgfx::init();
    }


}
