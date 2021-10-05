/*
 * This is a stand-alone header file. No ProfilerEditorWinodw.cpp is presented.
 */
#ifndef CORE_PROFILEREDITOR_H
#define CORE_PROFILEREDITOR_H

#include "core/Essentials.h"
#include "EditorWindow.h"

namespace core {

class ProfilerEditor : public EditorWindow {
public:
    ProfilerEditor(ImGuiID& parent, ImGuiDir direction, float size)
    : EditorWindow(parent, "Profiler", direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0/Double(ImGui::GetIO().Framerate), Double(ImGui::GetIO().Framerate));
        // TODO: Implement Profiler
    }

};

} // namespace core

#endif //CORE_PROFILEREDITOR_H
