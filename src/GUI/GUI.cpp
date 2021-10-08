#include <core/GUI/GUI.h>
#include <Magnum/ImGuiIntegration/Integration.h>
#include <misc/cpp/imgui_stdlib.h>

namespace core {

bool GUI::Button(const string &label, Vector2 size) {
    // TODO: PushID
    return ImGui::Button(label.c_str(), ImVec2(size));
}
bool GUI::CheckBox(const string& label, bool* value) {
    // TODO: PushID
    return ImGui::Checkbox(label.c_str(), value);
}
void GUI::Text(const string &text) {
    // TODO: PushID
    ImGui::Text(text.c_str());
}

}