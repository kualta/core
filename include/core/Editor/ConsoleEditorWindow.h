#ifndef CORE_CONSOLEEDITORWINDOW_H
#define CORE_CONSOLEEDITORWINDOW_H

#include "core/Essentials.h"
#include "core/Editor/EditorWindow.h"

namespace core {

class ConsoleWindow : public EditorWindow {
    ConsoleWindow(ImGuiID& parent, ImGuiDir direction, float size)
    : EditorWindow(parent, "Console", direction, size)
    {

    }

    void DrawWindowContent() override {
        ImGui::Text("Console... Logging... Beep Boop...");
        // TODO: Implement Console
    }


};
}

#endif //CORE_CONSOLEEDITORWINDOW_H
