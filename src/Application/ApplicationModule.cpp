#include <core/Application/ApplicationModule.h>
#include <core/GUI/GUIContext.h>
#include <core/Input/InputModule.h>

namespace core {

ApplicationModule::ApplicationModule(InputModule* inputModule)
: IModule("Application", WINDOW), inputModule(inputModule)
{

}
void ApplicationModule::Start() {
    inputModule->OnViewportEvent.Subscribe([&] (ViewportEvent& event)
                                           { GL::defaultFramebuffer.setViewport({{ }, event.GetFramebufferSize()}); } );
}
void ApplicationModule::EarlyTick() {
    for (auto app : apps) {
        app->ClearBuffers();
    }
}
void ApplicationModule::LateTick() {
    SwapRedraw();
}
void ApplicationModule::CreateApplication(const string &title, Rect rect) {
    apps.push_back(new Application(title, rect));
}
void ApplicationModule::SwapRedraw() {
    for (auto app : apps) {
        app->SwapBuffers();
        app->Redraw();
    }
}
void ApplicationModule::Redraw() {
    for (auto app : apps) {
        app->Redraw();
    }
}
Vector2i ApplicationModule::GetWindowSize(uint32_t id) {
    return apps[id]->GetWindowSize();
}
Vector2 ApplicationModule::GetWindowDpiScale(uint32_t id) {
    return apps[id]->GetDpiScaling();
}
Vector2i ApplicationModule::GetFrameBufferSize(uint32_t id) {
    return apps[id]->GetFrameBufferSize();
}

}