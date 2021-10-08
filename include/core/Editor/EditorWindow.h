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

    void AddCustomStyle(ImGuiCol colorVar, ImVec4 newvalue);
    void ApplyCustomStyles();
    void RemoveCustomStyles();

protected:


    struct customStyle {
        ImGuiCol colorVar;
        ImVec4   newvalue;
        ImVec4   oldValue;
    };

    string              title;
    ImGuiID             dockID;
    bool                isOpen  { true };
    ImGuiWindowFlags    flags   { 0 };
    std::vector<customStyle> customStyles;

private:

    virtual void DrawWindowContent() = 0;

};

} // namespace core

#endif //CORE_EDITORWINDOW_H
