#include <core/WindowPool.h>
#include <core/LogManager.h>

#include <list>
#include <memory>
#include <iostream>


namespace core {

std::list<std::shared_ptr<Window>> core::WindowPool::windowsPool;

void WindowPool::AddWindowToPool(const std::shared_ptr<Window>& windowPtr) {
    windowsPool.push_back(windowPtr);
}
void WindowPool::AddWindowToPool(const Window &window) {
    windowsPool.push_back(std::make_shared<core::Window>(window));
}
void WindowPool::DestroyAll() {
    windowsPool.erase(windowsPool.begin(), windowsPool.end());
    LogManager::LogInfo("Destroyed all windows successfully", WINDOW);
}


} // namespace