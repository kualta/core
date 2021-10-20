/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
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
        viewportNeedsReload = true;
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

        // clear any previous layout
        ImGui::DockBuilderRemoveNode(dockSpaceID);
        ImGui::DockBuilderAddNode(dockSpaceID, dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);

        ImGuiID centerSplitID = dockSpaceID;
        ImGuiID rightSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Right, 0.2f, nullptr, &centerSplitID);
        ImGuiID downSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Down, 0.15f, nullptr, &centerSplitID);
        ImGuiID leftSplitID = ImGui::DockBuilderSplitNode(centerSplitID, ImGuiDir_Left, 0.15f, nullptr, &centerSplitID);

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
    if (viewportNeedsReload) { ReloadViewport(); }

    BeginEditorDockSpace();

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
    PushDockStyle();

    ImGui::Begin("DockSpace", nullptr, windowFlags);
    dockSpaceID = ImGui::GetID(editorDockSpaceName.c_str());
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    ImGui::End();

    PopDockStyle();
}
void EditorModule::ReloadViewport() {
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    viewportNeedsReload = false;
}
void EditorModule::PushDockStyle() const {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
}

}

