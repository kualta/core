#ifndef INTERFACERS_WINDOW_H
#define INTERFACERS_WINDOW_H

#include <SDL.h>
#include <string>

#include "context.h"

namespace core {

    class Window {

    public:
        Window(SDL_Rect);
        ~Window();

        std::string title;
        SDL_Window *sdlWindow;
        Context m_Context;

    protected:
    private:

    };

}

#endif //INTERFACERS_WINDOW_H
