#include <core/Modules/ApplicationModule.h>

namespace core {

ApplicationModule::ApplicationModule()
: IModule("Application", WINDOW)
{

}
ApplicationModule::~ApplicationModule() {

}
void ApplicationModule::EarlyTick() {
    EarlyUpdateApps();
}
void ApplicationModule::Tick() {
    UpdateApps();
}
void ApplicationModule::CreateApplication(const string &title, Rect rect) {
    apps.push_back(new Application(title, rect));
}
void ApplicationModule::EarlyUpdateApps() {
    for (auto app : apps) {
        app->resetEvent();
    }
}
void ApplicationModule::UpdateApps() {
    for (auto app : apps) {
        app->mainLoopIteration();
    }
}

}