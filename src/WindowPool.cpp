#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/Window.h>

#include <memory>


namespace core {

std::vector<std::shared_ptr<Window>> WindowPool::windowsPool;

void WindowPool::AddWindowToPool(const std::shared_ptr<Window>& windowPtr) {
    windowsPool.push_back(windowPtr);
}
void WindowPool::AddWindowToPool(const Window &window) {
    windowsPool.push_back(std::make_shared<core::Window>(window));
}
void WindowPool::DestroyAll() {
    windowsPool.erase(windowsPool.begin(), windowsPool.end());
    Logger::LogInfo("Destroyed all windows successfully", WINDOW);
}


} // namespace