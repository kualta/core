#include <Window.h>
#include "Utility.h"


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
uint32_t Window::GetWindowID() const {
    return id_;
}
uint32_t Window::GetHeight() const {
    return height_;
}
uint32_t Window::GetWidth() const {
    return width_;
}
Vector2 Window::GetPosition() const {
    return position_;
}
std::string Window::GetTitle() const {
    return title_;
}
int Window::SetPosition(Vector2 pos) {
    if (pos.x < 0 || pos.y < 0) {
        LogManager::LogError("Changing window position", WINDOW);
        return -1;
    }
    position_ = pos;

    return 0;
}
SDL_Window *Window::GetSDLWindowPtr() const {
    return sdl_window_;
}

}
