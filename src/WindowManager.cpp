#include "WindowManager.h"
#include <string>

namespace core {

uint32_t WindowManager::SpawnWindow(const std::string& title, const Rect& rect) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, rect);
    AddWindowToPool(windowPtr);

    return windowPtr->GetId();
}
uint32_t WindowManager::SpawnWindow(const std::string &title, const Vector2& pos, int width, int height) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, Rect(pos, width, height));
    AddWindowToPool(windowPtr);

    return windowPtr->GetId();
}
uint32_t WindowManager::SpawnWindow(const std::string &title, const Vector2& pos, const Vector2& res) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, Rect(pos, res));
    AddWindowToPool(windowPtr);

    return windowPtr->GetId();
}
void WindowManager::AddWindowToPool(const std::shared_ptr<Window>& windowPtr) {
    windowsPool.push_back(windowPtr);
}
void WindowManager::AddWindowToPool(const Window &window) {
    windowsPool.push_back(std::make_shared<Window>(window));
}
void WindowManager::DestroyAll() { for (auto const& window: windowsPool) {
        SDL_DestroyWindow(window->GetSdlWindowPtr());
        delete &window;
    }
}
WindowManager::WindowManager() {
    SDL_Init(0);
}

}