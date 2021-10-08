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
    ImGui::Begin(title.c_str(), &isOpen, flags);
        DrawWindowContent();
    ImGui::End();
}
void EditorWindow::AddCustomStyle(ImGuiCol colorVar, ImVec4 newvalue) {
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec4 oldValue = colors[colorVar];
    customStyles.push_back({colorVar, newvalue, oldValue});
}
void EditorWindow::ApplyCustomStyles() {
    ImVec4* colors = ImGui::GetStyle().Colors;
//    colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);
    for (auto& style : customStyles) {
        Log() << style.colorVar << " " << style.newvalue.z;
        colors[style.colorVar] = style.newvalue;
    }
}
void EditorWindow::RemoveCustomStyles() {
//    ImVec4* colors = ImGui::GetStyle().Colors;
//    colors[ImGuiCol_WindowBg] = ImVec4(1, 1, 1, 1);
    ImVec4* colors = ImGui::GetStyle().Colors;
    for (auto& style : customStyles) {
        Log() << style.colorVar << " " << style.oldValue.z;
        colors[style.colorVar] = style.oldValue;
    }
}

}