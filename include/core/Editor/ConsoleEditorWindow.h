#ifndef CORE_CONSOLEEDITORWINDOW_H
#define CORE_CONSOLEEDITORWINDOW_H

#include "core/Essentials.h"
#include "core/Editor/EditorWindow.h"

namespace core {

class ConsoleWindowEditorWindow : public EditorWindow {
public:
    ConsoleWindowEditorWindow(ImGuiID& dockID) : EditorWindow(dockID, "Console") {

    }

protected:

    void DrawWindowContent() override {
        ImGui::Text("Console... Logging... Beep Boop...");
        // TODO: Implement Console
    }


};
}

#endif //CORE_CONSOLEEDITORWINDOW_H
