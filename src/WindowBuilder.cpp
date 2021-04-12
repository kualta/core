#include <core/WindowBuilder.h>
#include <core/WindowPool.h>
#include <core/Window.h>
#include <core/Renderer.h>
#include <core/Geometry.h>
#include <core/Logger.h>

#include <string>
#include <memory>

namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, rect);
    WindowPool::AddWindowToPool(windowPtr);
    core::Logger::LogInfo("Created window succesfully", core::WINDOW);

    // FIXME: Renderer initialization goes out of the scope of this function
    core::Renderer::InitWindow(*windowPtr);

    return windowPtr->GetId();
}


} // namespace core