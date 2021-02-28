#ifndef INTERFACERS_WINDOW_H
#define INTERFACERS_WINDOW_H

#include <SDL.h>
#include <string>

#include "context.h"
#include "geometry.h"

namespace core {

    class Window {

    public:
        Window(const std::string& t, const Vector2& pos, Rect& r);
        ~Window();

    protected:

    private:
        Vector2 position;
        int height;
        int width;
        core::Context context;
        SDL_Window *sdlWindow;
        std::string title;
    };

}

#endif //INTERFACERS_WINDOW_H
