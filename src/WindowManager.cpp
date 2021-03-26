#include "WindowManager.h"
#include "LogManager.h"
#include "RenderManager.h"
#include "WindowBuilder.h"
#include <string>

namespace core {

std::vector<std::shared_ptr<Window>> WindowManager::windowsPool {};

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
    SDL_Init(SDL_INIT_EVERYTHING);
}


}