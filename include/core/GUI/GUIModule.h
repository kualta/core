#ifndef CORE_GUIMODULE_H
#define CORE_GUIMODULE_H

#include <core/Essentials.h>
#include <core/GUI/GUIContext.h>
#include <core/IModule.h>

#include <core/Input/InputModule.h>

using namespace Magnum;
namespace core {

class GUIModule : public IModule {
public:
    explicit GUIModule(ApplicationModule* appModule, InputModule* inputModule);

protected:

    void UpdateGUI();
    void DrawGUI();

    void Start() override;
    void EarlyTick() override;
    void Tick() override;

    void SetStandardStyle();
    void SetStandardFont(float ratio);
    void SubscribeToEvents();

    GUIContext         gui { NoCreate };
    ApplicationModule* appModule;
    InputModule*       inputModule;

    void SetDefaultConfig();
};

}

#endif //CORE_GUIMODULE_H
