#include <core/Editor/EditorModule.h>
#include <core/Editor/HierarchyEditorWindow.h>
#include <core/Editor/ProfilerEditorWindow.h>
#include <core/Editor/InspectorEditorWindow.h>
#include <core/Editor/ConsoleEditorWindow.h>
#include <core/Editor/SceneViewEditorWindow.h>
#include <core/CameraList.h>

namespace core {

EditorModule::EditorModule(GUIModule* guiModule, InputModule* inputModule, SceneModule* sceneModule)
: IModule("Editor", EDITOR),
inputModule(inputModule),
guiModule(guiModule),
sceneModule(sceneModule),
sceneView(NoCreate)
{
    editorDockSpaceName = "EditorDockSpace";
    dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    windowFlags = ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_NoDocking
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoBringToFrontOnFocus
                | ImGuiWindowFlags_NoNavFocus
                | ImGuiWindowFlags_NoBackground;
}
void EditorModule::Start() {
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    inputModule->OnViewportEvent.Subscribe([&](ViewportEvent& event) {
        viewport = ImGui::GetMainViewport();
    });

    sceneView = SceneView({ 0, 0 }, { 100, 100 });
    Camera* sceneCamera = CameraList::Get()->GetSceneViewCamera();
    if (sceneCamera) {
        sceneCamera->SetView(sceneView);
    }

    ConstructDockSpace();
}
void EditorModule::ConstructDockSpace() {
    viewport = ImGui::GetMainViewport();

    ImGui::NewFrame();
    ImGui::Begin("DockSpace", nullptr, windowFlags);

    {
        dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

        ImGui::DockBuilderRemoveNode(dockSpaceID); // clear any previous layout
        ImGui::DockBuilderAddNode(dockSpaceID, dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);

        // TODO: Change AddWindow to take dock space instead of creating it
        ImGuiID centerSplitID = dockSpaceID;
        ImGuiID rightSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Right, 0.35, nullptr, &centerSplitID);
        ImGuiID downSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Down, 0.2, nullptr, &centerSplitID);
        ImGuiID leftSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Left, 0.25, nullptr, &centerSplitID);

        AddWindow<InspectorEditorWindow>(rightSplitID);
        AddWindow<ProfilerEditorWindow>(downSplitID);
        AddWindow<ConsoleWindowEditorWindow>(downSplitID);
        AddWindow<HierarchyEditorWindow>(leftSplitID);
        AddWindow<SceneViewEditorWindow>(centerSplitID);

        ImGui::DockBuilderFinish(dockSpaceID);
    }

    ImGui::End();
    ImGui::EndFrame();
}
void EditorModule::OnGUI() {
    PushDockStyle();
    BeginEditorDockSpace();
    PopDockStyle();

    for (auto &editorWindow : windows) {
        // CustomStyles were added to make SceneView window render no background, since FrameBuffer is rendered
        // behind it, yet it doesn't work because of some ImGui internal holes. Currently making all floating windows
        // transparent as temporary solution, but, please, FIXME!
        editorWindow->ApplyCustomStyles();
        editorWindow->Draw();
        editorWindow->RemoveCustomStyles();
    }
}
void EditorModule::PopDockStyle() const {
    ImGui::PopStyleVar(3);
}
void EditorModule::BeginEditorDockSpace() {
    ImGui::Begin("DockSpace", nullptr, windowFlags);
    dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    ImGui::End();
}
void EditorModule::PushDockStyle() const {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
}

}

