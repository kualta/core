#include <window.h>

#include <iostream>

namespace core {

    Window::Window(const std::string& title, core::Rect& rect) {

        this->title = title;

        sdlWindow = SDL_CreateWindow(title.c_str(),
                                     rect.x, rect.y,
                                     rect.w, rect.h,
                                     0);



    }

    Window::Window(const std::string& title, core::Rect& rect, Context& c) {

        this->title = title;

        sdlWindow = SDL_CreateWindow(title.c_str(),
                                     rect.x, rect.y,
                                     rect.w, rect.h,
                                     0);

    }

    Window::~Window() {
        SDL_DestroyWindow(sdlWindow);
    }

}
