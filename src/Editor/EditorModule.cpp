#include <core/Editor/EditorModule.h>
#include <core/Editor/SceneGraphEditorWindow.h>

namespace core {

const string        EditorModule::editorDockSpaceName { "EditorDockSpace" };
ImGuiDockNodeFlags  EditorModule::dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
ImGuiWindowFlags    EditorModule::windowFlags =
          ImGuiWindowFlags_MenuBar
        | ImGuiWindowFlags_NoDocking
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBackground;

EditorModule::EditorModule(GUIModule* guiModule, InputModule* inputModule)
: guiModule(guiModule), inputModule(inputModule)
{

}
void EditorModule::Start() {
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    inputModule->OnViewportEvent.Subscribe([&](ViewportEvent& event) {
        viewport = ImGui::GetMainViewport();
        viewportNeedsReload = true;
    });

    ConstructDockSpace();
}
void EditorModule::ConstructDockSpace() {
    viewport = ImGui::GetMainViewport();

    ImGui::NewFrame();
    ImGui::Begin("DockSpace", nullptr, windowFlags);

    {
        dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
        ImGui::DockBuilderRemoveNode(dockSpaceID); // clear any previous layout
        ImGui::DockBuilderAddNode(dockSpaceID, dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);

        ImGuiID sceneGraphID = AddWindow<SceneGraphEditorWindow>(dockSpaceID, "Scene Graph", ImGuiDir_Left, 0.2f);

        // Dock windows into the docking nodes
        for (auto& window : windows) {
            ImGui::DockBuilderDockWindow(window->GetTitle().c_str(), window->GetDockID());
        }

        ImGui::DockBuilderFinish(dockSpaceID);
    }

    ImGui::End();
    ImGui::EndFrame();
}
void EditorModule::OnGUI() {
    if (viewportNeedsReload) { ReloadViewport(); }

    PushDockStyle();
    BeginEditorDockSpace();
    PopDockStyle();

    for (auto &editorWindow : windows) {
        editorWindow->Draw();
    }
}
void EditorModule::PopDockStyle() const {
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
}
void EditorModule::BeginEditorDockSpace() {
    ImGui::Begin("DockSpace", nullptr, windowFlags);
    dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    ImGui::End();
}
void EditorModule::ReloadViewport() const {
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
}
void EditorModule::PushDockStyle() const {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
}

}

