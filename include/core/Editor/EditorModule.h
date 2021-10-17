#ifndef CORE_EDITORMODULE_H
#define CORE_EDITORMODULE_H

#include <core/Essentials.h>
#include <core/GUI/GUIModule.h>
#include <core/GUI/GUIBehaviour.h>
#include <core/IModule.h>
#include <core/GUI/GUI.h>
#include <core/Editor/EditorWindow.h>
#include <core/Scene/SceneView.h>

namespace core {

class EditorModule : public IModule, public GUIBehaviour {
public:
    explicit EditorModule(GUIModule* guiModule, InputModule* inputModule, SceneModule* sceneModule);

    template<typename T>
    ImGuiID AddWindow(ImGuiID dockID);

protected:

    void Start() override;
    void OnGUI() override;

    void PushDockStyle() const;
    void PopDockStyle() const;
    void ReloadViewport();
    void BeginEditorDockSpace();
    void ConstructDockSpace();

    InputModule*        inputModule;
    GUIModule*          guiModule;
    SceneModule*        sceneModule;

    ImGuiViewport*      viewport;
    SceneView           sceneView;
    ImGuiID             dockSpaceID;
    string              editorDockSpaceName;

    ImGuiDockNodeFlags  dockSpaceFlags;
    ImGuiWindowFlags    windowFlags;

    std::vector<unique<EditorWindow>> windows;

};

} // namespace core

#include "EditorModule.tpp"

#endif //CORE_EDITORMODULE_H
