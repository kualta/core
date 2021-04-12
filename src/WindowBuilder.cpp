#include <core/WindowBuilder.h>
#include <core/Window.h>
#include <core/Geometry.h>
#include <core/Vector.h>
#include <core/Renderer.h>
#include <core/WindowPool.h>
#include <core/Logger.h>
#include <core/Essential.h>

#include <string>
#include <memory>

namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::shared_ptr<Window> windowPtr = std::make_shared<Window>(title, rect);
    WindowPool::AddWindowToPool(windowPtr);
    core::Logger::LogInfo("Created window succesfully", core::WINDOW);

    core::Renderer::CreateRenderer(*windowPtr);

    return windowPtr->GetId();
}


} // namespace core