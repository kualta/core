#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

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
        std::string title_;
        SDL_Window *sdl_window_;
        Context context_;
        Vector2 position_;
        int height_;
        int width_;
    };


}

#endif //CORE_WINDOW_H
