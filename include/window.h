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

        friend Window GetWindowByID(unsigned int uid);

    private:
        SDL_Window *sdl_window_;
        std::string title_;
        unsigned int uid_;
        Vector2 position_;
        Context context_;
        int height_;
        int width_;
    };



}

#endif //CORE_WINDOW_H
