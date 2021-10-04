#include <core/EditorWindow.h>

namespace core {

EditorWindow::EditorWindow(const string &title) : title(title) {

}
string EditorWindow::GetTitle() {
    return title;
}
void EditorWindow::Draw() {
    ImGui::Begin(title.c_str());
        DrawWindowContent();
    ImGui::End();
}

}