#include "WindowPool.h"
#include "LogManager.h"

#include <list>
#include <memory>

namespace core {

std::list<std::shared_ptr<Window>> core::WindowPool::windowsPool;

void WindowPool::AddWindowToPool(const std::shared_ptr<Window>& windowPtr) {
    windowsPool.push_back(windowPtr);
}
void WindowPool::AddWindowToPool(const Window &window) {
    windowsPool.push_back(std::make_shared<core::Window>(window));
}
void WindowPool::DestroyAll() {
    for (auto window: windowsPool) {
        SDL_DestroyWindow(window->GetSdlWindowPtr());
        LogManager::LogInfo("Destroyed window successfully", WINDOW);
        if (window.use_count() == 1) {
            delete &window;
        } else {
            LogManager::LogError("Cannot delete window since it has outside pointers to it");
        }
    }
}


} // namespace