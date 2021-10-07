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
    ProfilerEditorWindow(ImGuiID& parent, ImGuiDir direction, float size)
    : EditorWindow(parent, "Profiler", direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0/Double(ImGui::GetIO().Framerate), Double(ImGui::GetIO().Framerate));
        // TODO: Implement Profiler
    }

};

} // namespace core

#endif //CORE_PROFILEREDITORWINDOW_H
