#include <window.h>

#include <iostream>

namespace core {

    Window::Window(const std::string& title, const Vector2& pos, core::Rect& rect) {

        this->title = title;
        this->position = pos;

        sdlWindow = SDL_CreateWindow(title.c_str(),
                                     rect.x, rect.y,
                                     rect.w, rect.h,
                                     0);



    }


    Window::~Window() {
        SDL_DestroyWindow(sdlWindow);
    }

}
