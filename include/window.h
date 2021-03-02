#ifndef INTERFACERS_WINDOW_H
#define INTERFACERS_WINDOW_H

#include <SDL.h>
#include <string>

#include "context.h"
#include "geometry.h"

namespace core {

    class Window {

    public:
        Window(const std::string &title, core::Rect &rect);
        ~Window();

    private:
        SDL_Window *sdlWindow;
        std::string title;
        Context context;
        Vector2 position;
        int height;
        int width;
    };

}

#endif //INTERFACERS_WINDOW_H
