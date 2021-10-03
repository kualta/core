#ifndef CORE_GUIMODULE_H
#define CORE_GUIMODULE_H

#include <core/Essentials.h>
#include <core/GUIContext.h>
#include <core/IModule.h>

#include <core/Modules/InputModule.h>

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


    GUIContext   gui { NoCreate };
    ApplicationModule* appModule;
    InputModule* inputModule;

};

}

#endif //CORE_GUIMODULE_H
