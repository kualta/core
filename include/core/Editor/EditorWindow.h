#ifndef CORE_EDITORWINDOW_H
#define CORE_EDITORWINDOW_H

#include "core/Essentials.h"
#include "core/GUI/GUI.h"

namespace core {

class EditorWindow {
public:
    explicit EditorWindow(ImGuiID dockID, string title = "EditorWindow");

    string GetTitle();
    ImGuiID GetDockID();

    virtual void Draw() final;

    std::vector<std::pair<ImGuiCol, const ImVec4&>> styles;

protected:

    string title;
    ImGuiID dockID;
    ImGuiWindowFlags flags { 0 };
    bool* isOpen;

private:

    virtual void DrawWindowContent() = 0;
};

}

#endif //CORE_EDITORWINDOW_H
