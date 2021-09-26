#ifndef CORE_GUIMODULE_H
#define CORE_GUIMODULE_H

#include <core/Essentials.h>
#include <core/IModule.h>

#include <Magnum/ImGuiIntegration/Context.hpp>

using namespace Magnum;
namespace core {

class GUIModule : public IModule {
public:
    explicit GUIModule(ApplicationModule* appModule);

    template<class KeyEvent>
    bool HandleKeyEvent(KeyEvent& event, bool value);

    template<class MouseEvent>
    bool HandleMouseEvent(MouseEvent& event, bool value);

protected:

    void UpdateGUI();
    void DrawGUI();

    void Start() override;
    void EarlyTick() override;
    void Tick() override;

    ImGuiIntegration::Context imgui { NoCreate };
    ApplicationModule* appModule;

    void SetStandardStyle();

    void SetStandardFont(float ratio);
};

#include "GUIModule.tpp"

}

#endif //CORE_GUIMODULE_H
