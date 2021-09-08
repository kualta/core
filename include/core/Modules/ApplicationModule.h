#ifndef CORE_APPLICATIONMODULE_H
#define CORE_APPLICATIONMODULE_H

#include <core/Essential.h>
#include <core/IModule.h>
#include <core/Application.h>

namespace core {

class ApplicationModule : public IModule {
public:
    ApplicationModule();
    ~ApplicationModule();

    void CreateApplication(const string &title = "Core Application",
                           Rect rect = { 0, 0, 1280, 720 });

protected:

    void Tick() override;
    void UpdateApps();

private:

    std::vector<Application*> apps;

};

}

#endif //CORE_APPLICATIONMODULE_H
