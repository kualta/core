#include <core/Editor/EditorWindow.h>
#include <core/Logger.h>

#include <utility>

namespace core {

EditorWindow::EditorWindow(ImGuiID dockID, string title)
: title(std::move(title)), dockID(dockID)
{
    ImGui::DockBuilderDockWindow(GetTitle().c_str(), dockID);
}
string EditorWindow::GetTitle() {
    return title;
}
ImGuiID EditorWindow::GetDockID() {
    return dockID;
}
void EditorWindow::Draw() {
    ImGui::Begin(title.c_str(), isOpen, flags);
        DrawWindowContent();
    ImGui::End();
}

}