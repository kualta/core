#include "core.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"


namespace core {
int Initialize() {
    // TODO: Simplify logging syntax
    if ( InitWindow() != 0 ) {
        LogManager::GetInstance().Log(ERR,"Window initialization failed, terminating");
        //SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Fatal! Window initialization failed: %s", SDL_GetError());
        return 1;
    }
    if ( InitRender() != 0 ) {
        LogManager::GetInstance().Log(ERR, "Render initialization failed, terminating");
        return 1;
    }
    if ( InitInput() != 0 ) {
        LogManager::GetInstance().Log(ERR, "Input initialization failed, terminating");
        return 1;
    }
    if ( InitSound() != 0 ) {
        LogManager::GetInstance().Log(ERR, "Sound initialization failed, terminating");
        return 1;
    }

    SDL_Quit();

    LogManager::GetInstance().Log(INFO, "- core initialization complete -");
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
    // we are calling bgfx::init() with no parameters on this step. We have to call another initialization func
    // after the window was created.

    bgfx::init();
    return 0;
}
int InitInput() {
    return 0;
}
int InitSound() {
    return 0;
}


}
