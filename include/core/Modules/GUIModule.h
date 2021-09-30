#ifndef CORE_GUIMODULE_H
#define CORE_GUIMODULE_H

#include <core/Essentials.h>
#include <core/IModule.h>

#include <Magnum/ImGuiIntegration/Context.hpp>
#include <core/GUIContext.h>

using namespace Magnum;
namespace core {

class GUIModule : public IModule {
public:
    explicit GUIModule(ApplicationModule* appModule);

protected:

    void UpdateGUI();
    void DrawGUI();

    void Start() override;
    void EarlyTick() override;
    void Tick() override;

    GUIContext imgui { NoCreate };
    ApplicationModule* appModule;

    void SetStandardStyle();

    void SetStandardFont(float ratio);
};

}

#endif //CORE_GUIMODULE_H
