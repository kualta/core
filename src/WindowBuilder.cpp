#include <string>
#include "Vector2.h"
#include "RenderManager.h"
#include "LogManager.h"
#include "WindowManager.h"
#include "WindowBuilder.h"
#include "WindowPool.h"


namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::shared_ptr<core::Window> windowPtr = std::make_shared<core::Window>(title, rect);
    WindowPool::AddWindowToPool(windowPtr);
    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    core::RenderManager::CreateRenderer(*windowPtr);

    return windowPtr->GetId();
}
uint32_t WindowBuilder::SpawnWindow(const std::string &title, const Vector2& pos, int width, int height) {
    std::shared_ptr<core::Window> windowPtr = std::make_shared<core::Window>(title, core::Rect(pos, width, height));
    WindowPool::AddWindowToPool(windowPtr);

    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    return windowPtr->GetId();
}
uint32_t WindowBuilder::SpawnWindow(const std::string &title, const Vector2& pos, const Vector2& res) {
    std::shared_ptr<core::Window> windowPtr = std::make_shared<core::Window>(title, core::Rect(pos, res));
    WindowPool::AddWindowToPool(windowPtr);

    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    return windowPtr->GetId();
}


}