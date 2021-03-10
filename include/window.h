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

        friend Window GetWindowID();

    private:
        static uint32_t win_counter_;

        SDL_Window *sdl_window_;

        std::string title_;
        Vector2 position_;
        Context context_;
        uint32_t height_;
        uint32_t width_;

        uint32_t id_;
    };



}

#endif //CORE_WINDOW_H
