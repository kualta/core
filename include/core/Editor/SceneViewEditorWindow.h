#ifndef CORE_SCENEVIEWEDITORWINDOW_H
#define CORE_SCENEVIEWEDITORWINDOW_H

#include "core/Essentials.h"
#include "core/Logger.h"
#include "core/GUI/GUI.h"
#include "core/Editor/EditorWindow.h"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>
#include "Magnum/ImGuiIntegration/Integration.h"


namespace core {

class SceneViewEditorWindow : public EditorWindow {
public:
    SceneViewEditorWindow(ImGuiID& dockID)
    : EditorWindow(dockID, "Scene View") {
        flags |= ImGuiWindowFlags_NoBackground;
    }

    void DrawWindowContent() override {
        ImVec2 currentSize = ImGui::GetWindowSize();
        ImVec2 currentPos = ImGui::GetWindowPos();
        if (currentSize.x != size.x || currentSize.y != size.y || currentPos.x != pos.x || currentPos.y != pos.y) {
            size = currentSize;
            pos = currentPos;
            Resize();
        }
        GUI::Text(std::to_string(ImGui::GetWindowSize().x) + " " + std::to_string(ImGui::GetWindowSize().y));
        GUI::Text(std::to_string(ImGui::GetWindowPos().x) + " " + std::to_string(ImGui::GetWindowPos().y));
    }

protected:

    void Resize() {
        SceneView::Resize(Vector2i(pos.x, pos.y), Vector2i(size.x, size.y));
        SceneView::GetFrameBuffer().setViewport({ Vector2i(0, 0), Vector2i(size.x, size.y) });
    }

    static ImVec2 size;
    static ImVec2 pos;
};

ImVec2 SceneViewEditorWindow::size { 0, 0 };
ImVec2 SceneViewEditorWindow::pos { 0, 0 };

} // namespace core

#endif //CORE_SCENEVIEWEDITORWINDOW_H
