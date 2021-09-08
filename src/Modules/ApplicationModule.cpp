#include <core/Modules/ApplicationModule.h>

namespace core {

ApplicationModule::ApplicationModule()
: IModule("Application", WINDOW)
{

}
ApplicationModule::~ApplicationModule() {

}
void ApplicationModule::Tick() {
    UpdateApps();
}
void ApplicationModule::CreateApplication(const string &title, Rect rect) {
    apps.push_back(new Application(title, rect));
}
void ApplicationModule::UpdateApps() {
    for (auto app : apps) {
        app->mainLoopIteration();
    }
}

}