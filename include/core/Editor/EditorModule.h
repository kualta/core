#ifndef CORE_EDITORMODULE_H
#define CORE_EDITORMODULE_H

#include <core/Essentials.h>
#include <core/GUI/GUIModule.h>
#include <core/GUI/GUIBehaviour.h>
#include <core/IModule.h>
#include <core/GUI/GUI.h>
#include <core/Editor/EditorWindow.h>

namespace core {

class EditorModule : public IModule, public GUIBehaviour {
public:
    explicit EditorModule(GUIModule* guiModule, InputModule* inputModule);

    void Start() override;
    void OnGUI() override;

    template<typename T>
    ImGuiID AddWindow(ImGuiID parent, const string& title, ImGuiDir direction, float size = 0.5f);

protected:


    void PushDockStyle() const;
    void PopDockStyle() const;
    void ReloadViewport() const;
    void BeginEditorDockSpace();
    void ConstructDockSpace();


    GUIModule*      guiModule;
    InputModule*    inputModule;
    ImGuiViewport*  viewport;
    ImGuiID         dockSpaceID;
    bool            viewportNeedsReload { true };

    static const string         editorDockSpaceName;
    static ImGuiDockNodeFlags   dockSpaceFlags;
    static ImGuiWindowFlags     windowFlags;

    std::vector<unique<EditorWindow>> windows;

};

} // namespace core

#include "EditorModule.tpp"

#endif //CORE_EDITORMODULE_H
