#include <core/WindowBuilder.h>
#include "core/Window.h"
#include <core/Vector.h>
#include <core/RenderManager.h>
#include <core/WindowPool.h>
#include <core/LogManager.h>

#include <string>
#include <memory>

namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, rect);
    WindowPool::AddWindowToPool(windowPtr);
    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    core::RenderManager::CreateRenderer(*windowPtr);

    return windowPtr->GetId();
}
uint32_t WindowBuilder::SpawnWindow(const std::string &title, const Vector2& pos, int width, int height) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, Rect(pos, width, height));
    WindowPool::AddWindowToPool(windowPtr);

    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    return windowPtr->GetId();
}
uint32_t WindowBuilder::SpawnWindow(const std::string &title, const Vector2& pos, const Vector2& res) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, Rect(pos, res));
    WindowPool::AddWindowToPool(windowPtr);

    core::LogManager::LogInfo("Created window succesfully", core::WINDOW);

    return windowPtr->GetId();
}


}