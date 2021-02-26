#ifndef INTERFACERS_WINDOW_H
#define INTERFACERS_WINDOW_H

#include <SDL.h>
#include <string>

namespace core {

    class Window {

    public:
        Window();
        ~Window();

        std::string title;
        SDL_Window *sdlWindow;
    protected:
    private:

    };

}

#endif //INTERFACERS_WINDOW_H
