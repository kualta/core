#include <core/Editor/EditorWindow.h>
#include <core/Logger.h>

#include <utility>

namespace core {

EditorWindow::EditorWindow(ImGuiID& parent, string title, ImGuiDir direction, float size)
: size(size), title(std::move(title)), parentID(parent), direction(direction)
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