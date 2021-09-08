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

    void CreateApplication();

protected:

    void Tick() override;
    void UpdateApps();

private:

    std::vector<Application*> apps;

};

}

#endif //CORE_APPLICATIONMODULE_H
