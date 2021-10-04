#include <core/Editor/EditorWindow.h>

namespace core {

EditorWindow::EditorWindow(ImGuiID parent, const string& title, ImGuiDir direction, float size)
: parentID(parent), title(title), direction(direction), size(size)
{
    dockID = ImGui::DockBuilderSplitNode(parent, direction, size, nullptr, &parent);
}
string EditorWindow::GetTitle() {
    return title;
}
ImGuiID EditorWindow::GetDockID() {
    return dockID;
}
void EditorWindow::Draw() {
    ImGui::Begin(title.c_str());
        DrawWindowContent();
    ImGui::End();
}

}