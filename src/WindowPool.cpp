#include <string>
#include "WindowBuilder.h"
#include "RenderManager.h"
#include "LogManager.h"
#include "WindowManager.h"
#include "WindowPool.h"


namespace core {


std::vector<std::shared_ptr<Window>> core::WindowManager::windowsPool {};

void WindowPool::AddWindowToPool(const std::shared_ptr<Window>& windowPtr) {
    windowsPool.push_back(windowPtr);
}
void WindowPool::AddWindowToPool(const Window &window) {
    windowsPool.push_back(std::make_shared<core::Window>(window));
}
void WindowPool::DestroyAll() {
    for (auto const& window: windowsPool) {
        SDL_DestroyWindow(window->GetSdlWindowPtr());
        delete &window;
    }
}

}