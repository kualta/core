#include <window.h>
#include "utility.h"

namespace core {


Window::Window(const std::string &title, Rect& rect)
: title_(title), height_(rect.h), width_(rect.w), position_(rect.position), id_(++win_counter_) {
    this->position_ = Vector2(rect.position.x, rect.position.y);
    this->sdl_window_ = SDL_CreateWindow(title.c_str(),
                                         rect.position.x, rect.position.y,
                                         rect.w, rect.h,
                                         0);

    /// Add created window object to the windows pool.
    windows_pool.push_back(std::shared_ptr<Window>(this));
}
Window::~Window() {
    SDL_DestroyWindow(sdl_window_);
}
Window GetWindowID() {

}


}
