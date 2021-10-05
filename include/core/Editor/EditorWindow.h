#ifndef CORE_EDITORWINDOW_H
#define CORE_EDITORWINDOW_H

#include "core/Essentials.h"
#include "core/GUI/GUI.h"

namespace core {

class EditorWindow {
public:
    explicit EditorWindow(ImGuiID &parent,
                          string  title = "EditorWindow",
                          ImGuiDir direction = ImGuiDir_Right,
                          float size = 0.5f);

    string GetTitle();
    ImGuiID GetDockID();

    virtual void Draw() final;

protected:

    float size;
    string title;
    ImGuiID dockID;
    ImGuiID parentID;
    ImGuiDir direction;

private:

    virtual void DrawWindowContent() = 0;
};

}

#endif //CORE_EDITORWINDOW_H
