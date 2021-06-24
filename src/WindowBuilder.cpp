#include <core/Modules/WindowModule.h>
#include <core/Modules/IRenderModule.h>
#include <core/WindowBuilder.h>
#include <core/BgfxWindowRenderer.h>
#include <core/Window.h>
#include <core/Logger.h>
#include <core/Core.h>

#include <memory>
#include <string>

namespace core {

uint32_t WindowBuilder::SpawnWindow(const std::string& title, const Rect& rect) {
    auto window = std::make_unique<Window>(title, rect);
    Logger::Log(WINDOW, INFO) << "Created window \"" << title << "\" ";
    uint32_t windowId = window->GetId();

    // Pass new window to intialize renderer
    auto windowModule = Core::GetModule<WindowModule>();
    windowModule->renderModule->windowRenderer->InitWindow(*window);
    windowModule->windowPool.Register(std::move(window));
    return windowId;
}

} // namespace core