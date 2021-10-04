#include <core/Modules/EditorModule.h>

namespace core {

ImGuiDockNodeFlags EditorModule::dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
ImGuiWindowFlags EditorModule::windowFlags =
          ImGuiWindowFlags_MenuBar
        | ImGuiWindowFlags_NoDocking
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBackground;

EditorModule::EditorModule(GUIModule *guiModule) : guiModule(guiModule) {

}
void EditorModule::Start() {
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ConstructDockSpace();
}
void EditorModule::ConstructDockSpace() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::NewFrame();
    ImGui::Begin("DockSpace", nullptr, windowFlags);

    {
        dockspaceId = ImGui::GetID("MainDockSpace");
        ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
        ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

        // split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
        // window ID to split, direction, fraction (between 0 and 1), the final two setting lets us choose which id we
        // want (whichever one we DON'T set as NULL, will be returned by the function) out_id_at_dir is the id of the
        // node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
        auto dock_id_left = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.2f, nullptr, &dockspaceId);
        auto dock_id_down = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Down, 0.25f, nullptr, &dockspaceId);

        // we now dock our windows into the docking node we made above
        ImGui::DockBuilderDockWindow("Down", dock_id_down);
        ImGui::DockBuilderDockWindow("Left", dock_id_left);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    ImGui::End();
    ImGui::EndFrame();
}
void EditorModule::OnGUI() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace", nullptr, windowFlags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    dockspaceId = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

    ImGui::End();

    ImGui::Begin("Left");
    ImGui::Text("Hello, left!");
    ImGui::End();

    ImGui::Begin("Down");
    ImGui::Text("Hello, down!");
    ImGui::End();
}

}

