#include <core/GUI/GUI.h>
#include <Magnum/ImGuiIntegration/Integration.h>
#include <misc/cpp/imgui_stdlib.h>
#include <limits>

namespace core {

bool GUI::Button(const string& label, Vector2 size) {
    return ImGui::Button(label.c_str(), ImVec2(size));
}
bool GUI::CheckBox(const string& label, bool* value) {
    ImGui::PushID(value);
    bool out = ImGui::Checkbox(label.c_str(), value);
    ImGui::PopID();
    return out;
}
void GUI::Text(const string& text) {
    return ImGui::Text("%s", text.c_str());
}
bool GUI::IsHovered() {
    return ImGui::IsItemHovered();
}
bool GUI::IsActive() {
    return ImGui::IsItemActive();
}
bool GUI::IsFocused() {
    return ImGui::IsItemFocused();
}
void GUI::Tooltip(const string& text) {
    ImGui::SetTooltip("%s", text.c_str());
}
void GUI::TextLabel(const string& text, const string& label) {
    ImGui::LabelText(label.c_str(), text.c_str());
}

}