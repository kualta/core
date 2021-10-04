#ifndef CORE_EDITORMODULE_H
#define CORE_EDITORMODULE_H

#include <core/Essentials.h>
#include <core/Modules/GUIModule.h>
#include <core/GUIBehaviour.h>
#include <core/IModule.h>
#include <core/GUI.h>
#include <core/EditorWindow.h>

namespace core {

class EditorModule : public IModule, public GUIBehaviour {
public:
    explicit EditorModule(GUIModule* guiModule);

    void Start() override;
    void OnGUI() override;

    ImGuiID AddWindow();

protected:

    void ConstructDockSpace();

    GUIModule* guiModule;
    ImGuiID dockspaceId;
    static ImGuiDockNodeFlags dockspaceFlags;
    static ImGuiWindowFlags windowFlags;

    std::vector<unique<EditorWindow>> windows;

};
}

#endif //CORE_EDITORMODULE_H
