#ifndef CORE_H
#define CORE_H

#define SDL_MAIN_HANDLED
#define NULL 0

#include <SDL.h>
#include <SDL_syswm.h>

#include "context.h"
#include "geometry.h"
#include "logger.h"
#include "window.h"

namespace core {
    int Initialize();
    int Quit();

    int InitWindow();
    int InitSound();
    int InitInput();
    int InitNetwork();
    int InitPhysics();
    int InitRender();
}


#endif //CORE_H
