#ifndef INTERFACERS_WINDOW_H
#define INTERFACERS_WINDOW_H

#include <SDL.h>
#include <string>

#include "context.h"
#include "geometry.h"

namespace core {

    class Window {

    public:
        Window(const std::string& t, core::Rect& r, Context& c);
        Window(const std::string& t, Rect& r);
        ~Window();

    protected:

    private:
        core::Context context;
        SDL_Window *sdlWindow;
        std::string title;
    };

}

#endif //INTERFACERS_WINDOW_H
