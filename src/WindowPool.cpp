#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/Window.h>

#include <memory>


namespace core {

std::vector<std::shared_ptr<Window>> WindowPool::windowPool;

void WindowPool::RegisterWindow(const std::shared_ptr<Window>& windowPtr) {
    windowPool.push_back(windowPtr);
}
void WindowPool::RegisterWindow(const Window &window) {
    windowPool.push_back(std::make_shared<core::Window>(window));
}
WindowPool::~WindowPool() {
    Logger::Log(INFO, INTERNAL) << "Windows Pool destroyed successfully";
}


} // namespace