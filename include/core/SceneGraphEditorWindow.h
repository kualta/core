#ifndef CORE_SCENEGRAPHEDITORWINDOW_H
#define CORE_SCENEGRAPHEDITORWINDOW_H

#include "Essentials.h"
#include "EditorWindow.h"

namespace core {

class SceneGraphEditorWindow : public EditorWindow {
public:
    SceneGraphEditorWindow(ImGuiID parent,
                           const string& title,
                           ImGuiDir direction,
                           float size)
    : EditorWindow(parent, title, direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("Wow scene graph!");
    }

};

}

#endif //CORE_SCENEGRAPHEDITORWINDOW_H
