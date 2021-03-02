#ifndef INTERFACERS_CORE_H
#define INTERFACERS_CORE_H

#define SDL_MAIN_HANDLED
#define NULL 0

#include <SDL.h>

namespace core {
    int init();
    int InitWindow();
    int InitSound();
    int InitInput();
    int InitNetwork();
    int InitPhysics();
    int InitRender();
}


#endif //INTERFACERS_CORE_H
