/*
 * This is a stand-alone header file. No SceneGraphEditorWinodw.cpp is presented.
 */
#ifndef CORE_INSPECTOREDITORWINDOW_H
#define CORE_INSPECTOREDITORWINDOW_H

#include "core/Essentials.h"
#include "EditorWindow.h"

namespace core {

class InspectorEditorWindow : public EditorWindow {
public:
    InspectorEditorWindow(ImGuiID& parent,
                          const string& title,
                          ImGuiDir direction,
                          float size)
    : EditorWindow(parent, title, direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("No way!! Inspector it is!");
        // TODO: Add inspector
    }

};

}

#endif //CORE_INSPECTOREDITORWINDOW_H
