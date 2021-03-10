#include <window.h>
#include "utility.h"

namespace core {


    Window::Window(const std::string &title, Rect& rect)
    : title_(title), height_(rect.h), width_(rect.w), position_(rect.position)
    {

        this->position_ = Vector2(rect.position.x, rect.position.y);

        this->sdl_window_ = SDL_CreateWindow(title.c_str(),
                                             rect.position.x, rect.position.y,
                                             rect.w, rect.h,
                                             0);
    }


    Window::~Window() {
        SDL_DestroyWindow(sdl_window_);
    }
Window GetWindowByID(unsigned int uid) {
    return Window(std::basic_string(), core::Rect());
}

}
