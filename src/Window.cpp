#include <core/Window.h>
#include "core/Logger.h"
#include "core/Geometry.h"

#include <SDL.h>
#include <SDL_syswm.h>


namespace core {


Window::Window(const std::string &title, const Rect& rect)
  : title(title), height(rect.h), width(rect.w),
    position(rect.x, rect.y), sdlWmi(), Object(title + " Window") {
    this->sdlWindow = SDL_CreateWindow(title.c_str(),
                                       rect.x, rect.y,
                                       rect.w, rect.h,
                                       SDL_WINDOW_RESIZABLE);
    /// sdlWmi must be initialized with version
    SDL_VERSION(&sdlWmi.version);
    SDL_GetWindowWMInfo(this->sdlWindow, &sdlWmi);
}
Window::~Window() {
    SDL_DestroyWindow(sdlWindow);
}
uint32_t Window::GetHeight() const {
    return height;
}
uint32_t Window::GetWidth() const {
    return width;
}
Vector2 Window::GetPosition() const {
    return position;
}
std::string Window::GetTitle() const {
    return title;
}
void Window::SetPosition(const Vector2& pos) {
    if (pos.x < 0 || pos.y < 0) {
        Logger::Log(ERR, WINDOW) << "Changing window position failed";
        return;
    }
    position = pos;
}
SDL_Window* Window::GetSdlWindow() const {
    return sdlWindow;
}
SDL_SysWMinfo* Window::GetSdlWmi() const {
    return const_cast<SDL_SysWMinfo*>(&sdlWmi);
}

}
