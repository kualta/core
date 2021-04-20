#include <core/WindowBuilder.h>
#include <core/WindowPool.h>
#include <core/Window.h>
#include <core/Renderer.h>
#include <core/Geometry.h>
#include <core/Logger.h>
#include <core/Root.h>

#include <string>
#include <memory>

namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::unique_ptr<Window> windowPtr = std::move(std::make_unique<Window>(title, rect));
    Logger::Log(INFO, WINDOW) << "Created window succesfully";
    uint32_t windowId = windowPtr->GetId();

    // FIXME: Renderer initialization is out of the scope of this method, refactoring needed
    core::Renderer::InitWindow(*windowPtr);

    Root::GetInstancePtr()->windowPool->Register(std::move(windowPtr));


    return windowId;
}


} // namespace core