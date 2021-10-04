/*
 * This is a stand-alone header file. No ProfilerEditorWinodw.cpp is presented.
 */
#ifndef CORE_PROFILEREDITORWINDOW_H
#define CORE_PROFILEREDITORWINDOW_H

#include "core/Essentials.h"
#include "EditorWindow.h"

namespace core {

class ProfilerEditorWindow : public EditorWindow {
public:
    ProfilerEditorWindow(ImGuiID& parent,
                           const string& title,
                           ImGuiDir direction,
                           float size)
    : EditorWindow(parent, title, direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("Omg Profiler??");
        // TODO: Add profiler
    }

};

} // namespace core

#endif //CORE_PROFILEREDITORWINDOW_H
