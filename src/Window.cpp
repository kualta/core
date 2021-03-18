#include <Window.h>

#include <Root.h>
#include <Utility.h>


namespace core {


Window::Window(const std::string &title, const Rect& rect)
: title(title), height(rect.h), width(rect.w), position(rect.position) {
    this->id = Root::GetNewID();
    this->position = Vector2(rect.position.x, rect.position.y);
    this->sdlWindow = SDL_CreateWindow(title.c_str(),
                                         rect.position.x, rect.position.y,
                                         rect.w, rect.h,
                                         0);
}
Window::~Window() {
    SDL_DestroyWindow(sdlWindow);
}
uint32_t Window::GetWindowID() const {
    return id;
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
int Window::SetPosition(const Vector2& pos) {
    if (pos.x < 0 || pos.y < 0) {
        LogManager::LogError("Changing window position failed", WINDOW);
        return -1;
    }
    position = pos;

    return 0;
}
SDL_Window *Window::GetSdlWindowPtr() const {
    return sdlWindow;
}


}
