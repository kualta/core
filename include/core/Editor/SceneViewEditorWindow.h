#ifndef CORE_SCENEVIEWEDITORWINDOW_H
#define CORE_SCENEVIEWEDITORWINDOW_H

#include "core/Essentials.h"
#include "EditorWindow.h"

#include <Magnum/GL/DefaultFramebuffer.h>

namespace core {

class SceneViewEditorWindow : public EditorWindow {
public:
    SceneViewEditorWindow(ImGuiID& parent, ImGuiDir direction, float size)
    : EditorWindow(parent, "Scene View", direction, size) {

    }

    void DrawWindowContent() override {
        ImVec2 currentSize = ImGui::GetWindowSize();
        if (currentSize != size) {
            size = currentSize;
            Resize();
        }

    }

protected:

    void Resize() {
        ImVec2 pos = ImGui::GetWindowPos();
        GL::defaultFramebuffer.setViewport({ Vector2i { pos }, Vector2i { size }});
    }

    static ImVec2 size;
};

} // namespace core

#endif //CORE_SCENEVIEWEDITORWINDOW_H
