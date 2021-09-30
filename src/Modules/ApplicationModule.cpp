#include <core/Modules/ApplicationModule.h>
#include <core/GUIContext.h>

namespace core {

ApplicationModule::ApplicationModule()
: IModule("Application", WINDOW)
{

}
void ApplicationModule::EarlyTick() {
    for (auto app : apps) {
        app->ClearBuffers();
        app->mainLoopIteration();
    }
}
void ApplicationModule::Tick() {

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
void ApplicationModule::SetGuiContext(GUIContext* context, uint32_t id) {
    apps[id]->SetGuiContext(context);
}

}