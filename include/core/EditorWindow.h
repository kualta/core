#ifndef CORE_EDITORWINDOW_H
#define CORE_EDITORWINDOW_H

#include "Essentials.h"
#include "GUI.h"

namespace core {

class EditorWindow {
public:
    explicit EditorWindow(const string& title = "EditorWindow");

    string GetTitle();

private:
    virtual void Draw() final;
    virtual void DrawWindowContent() = 0;

    string title;
};

}

#endif //CORE_EDITORWINDOW_H
