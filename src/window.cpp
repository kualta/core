#include <window.h>

#include <iostream>

namespace core {

    Window::Window(const std::string &title, Rect &rect)
    : title(title), height(rect.h), width(rect.w)
    {

        this->position = new Vector2(rect.x, rect.y);

        this->sdlWindow = SDL_CreateWindow(title.c_str(),
                                     rect.x, rect.y,
                                     rect.w, rect.h,
                                     0);

    }


    Window::~Window() {
        SDL_DestroyWindow(sdlWindow);
    }

}
