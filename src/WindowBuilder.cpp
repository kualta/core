#include <core/WindowBuilder.h>
#include <core/WindowRenderer.h>
#include <core/Window.h>
#include <core/Logger.h>
#include <core/Root.h>

#include <string>
#include <memory>

namespace core {


uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    std::unique_ptr<Window> windowPtr = std::move(std::make_unique<Window>(title, rect));
    Logger::Log(INFO, INTERNAL) << "Created window \"" << title << "\" ";

    // Pass new window to intialize renderer
    WindowRenderer::InitWindow(*windowPtr);

    uint32_t windowId = windowPtr->GetId();

    Root::Get()->windowPool->Register(std::move(windowPtr));


    return windowId;
}


} // namespace core