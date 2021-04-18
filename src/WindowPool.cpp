#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/Window.h>

#include <memory>


namespace core {

std::vector<std::shared_ptr<Window>> WindowPool::windowPool;

void WindowPool::RegisterWindow(const std::shared_ptr<Window>& windowPtr) {
    windowPool.push_back(windowPtr);
}
WindowPool::~WindowPool() {
    Logger::Log(INFO, INTERNAL) << "Windows Pool destroyed successfully";
}


} // namespace